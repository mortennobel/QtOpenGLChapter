#include "counter.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Counter a, b, c;
    QObject::connect(&a, &Counter::valueChanged,
                     &b, &Counter::setValue);
    QObject::connect(&a, &Counter::valueChanged,
                     &c, &Counter::setValue);

    a.setValue(12);     // a.value() == 12, b.value() == 12, c.value() == 12
    b.setValue(48);     // a.value() == 12, b.value() == 48, c.value() == 12

    using namespace std;
    cout << "a "<<a.value()<<" b "<<b.value()<<" c "<<c.value()<<endl;

    return 0;
}
