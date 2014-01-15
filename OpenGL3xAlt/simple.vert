#version 150

in vec4 vertex;
in vec3 color;
uniform vec4 offset;
out vec3 vColor;

void main( void )
{
    gl_Position = vertex + offset;
    vColor = color;
}
