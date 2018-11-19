#include "Pin.h"
#include <util/delay.h>

#define delay(N) _delay_ms(N);

int main() {
    Pin a(2);
    Pin b(17);
    Pin c(9);
    Pin d(15);

    a.output();
    b.output();
    c.output();
    d.output();


    Pin *pins[] = {&a, &b, &c, &d};

    while (true) {

        for (int i = 0; i < 4; i++) {
            (*pins[i]).on();
            delay(1000);
            (*pins[i]).off();
        }
    }

    return 0;
}
