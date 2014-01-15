#include "trianglewindow.h"

#include <QFile>
#include <QString>
#include <QDebug>

using namespace std;

TriangleWindow::TriangleWindow(QSurfaceFormat surfaceFormat, QScreen *screen)
    :GLWindow(surfaceFormat, screen)
{
}

GLuint TriangleWindow::prepareShaderProgram( const QString& vertexShaderPath,
                                     const QString& fragmentShaderPath )
{
    struct Shader {
        const QString&  filename;
        GLenum       type;
        GLchar*      source;
    }  shaders[2] = {
        { vertexShaderPath, GL_VERTEX_SHADER, NULL },
        { fragmentShaderPath, GL_FRAGMENT_SHADER, NULL }
    };

    GLuint program = glCreateProgram();

    for ( int i = 0; i < 2; ++i ) {
        Shader& s = shaders[i];
        QFile file( s.filename );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qWarning() << "Cannot open file " << s.filename;
            exit( EXIT_FAILURE );
        }
        QByteArray data = file.readAll();
        file.close();
        s.source = data.data();

        if ( shaders[i].source == NULL ) {
            qWarning() << "Failed to read " << s.filename;
            exit( EXIT_FAILURE );
        }
        GLuint shader = glCreateShader( s.type );
        glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
        glCompileShader( shader );

        GLint  compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            qWarning() << s.filename << " failed to compile:" ;
            GLint  logSize;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
            auto logMsg = unique_ptr<char>(new char[logSize]);
            glGetShaderInfoLog( shader, logSize, NULL, logMsg.get() );
            qWarning() << logMsg.get();

            exit( EXIT_FAILURE );
        }

        glAttachShader( program, shader );
    }

    // Link output
    glBindFragDataLocation(program, 0, "fragColor");

    // link  and error check
    glLinkProgram(program);

    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        qWarning() << "Shader program failed to link";
        GLint  logSize;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetProgramInfoLog( program, logSize, NULL, logMsg );
        qWarning() << logMsg ;
        delete [] logMsg;

        exit( EXIT_FAILURE );
    }

    // use program object
    glUseProgram(program);

    return program;
}

void TriangleWindow::initializeGL()
{
    // must initialize opengl functions
    initializeOpenGLFunctions();

    // Prepare a complete shader program...
    m_shader = prepareShaderProgram( ":/simple.vert", ":/simple.frag" );

    // Create a interleaved triangle (vec3 position, vec3 color)
    float points[] = { -0.5f, -0.5f, 0.0f, 1.0f, 0.0, 0.0,
                        0.5f, -0.5f, 0.0f, 0.0f, 1.0, 0.0,
                        0.0f,  0.5f, 0.0f, 0.0f, 0.0, 1.0,  };
    glGenVertexArrays(1, &m_vertexBuffer);
    glBindVertexArray(m_vertexBuffer);
    GLuint  vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), points, GL_STATIC_DRAW);
    GLuint positionAttribute = glGetAttribLocation(m_shader, "vertex");
    GLuint colorAttribute = glGetAttribLocation(m_shader, "color");
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (const GLvoid *)0);
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (const GLvoid *)(sizeof(float)*3));
}

void TriangleWindow::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw stuff
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}

void TriangleWindow::resizeGL(int width, int height){
    // Set the viewport to window dimensions
    glViewport( 0, 0,  width, qMax( height, 1 ));
}
