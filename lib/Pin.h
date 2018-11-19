/* #include <avr/pgmspace.h> */
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define NOTEXISTS 0


const uint8_t PROGMEM pin_to_bit[] {
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7), // port d
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5),                 // port b
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5),                 // port c
};

volatile uint8_t * pin_to_port[] {
    &PORTD, &PORTD, &PORTD, &PORTD, &PORTD, &PORTD, &PORTD, &PORTD,
    &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB,
    &PORTC, &PORTC, &PORTC, &PORTC, &PORTC, &PORTB,
};

volatile uint8_t * pin_to_register[] {
    &DDRD, &DDRD, &DDRD, &DDRD, &DDRD, &DDRD, &DDRD, &DDRD,
    &DDRB, &DDRB, &DDRB, &DDRB, &DDRB, &DDRB,
    &DDRC, &DDRC, &DDRC, &DDRC, &DDRC, &DDRC,
};

volatile uint8_t* volatile_read_word(uint16_t P) {
    return (volatile uint8_t *) pgm_read_word(P);
};

void cbi(uint8_t sfr, uint8_t bit) {
    sfr &= ~(_BV(bit));
};

class Pin {
    private:
        uint8_t pin;

        uint8_t bit;
        volatile uint8_t *port;
        volatile uint8_t *reg;

    public:
        Pin(uint8_t number) {
            pin = number;

            bit = pin_to_bit[number];
            reg = pin_to_register[number];
            port = pin_to_port[number];
        }

        void output() {
            uint8_t oldSREG = SREG;
            cli();

            *reg |= bit;

            SREG = oldSREG;
        }

        void input() {
            uint8_t oldSREG = SREG;
            cli();

            *reg &= ~bit;
            *port &= ~bit; // off by default

            SREG = oldSREG;
        }

        void input_pullup() {
            uint8_t oldSREG = SREG;
            cli();

            *reg &= ~bit;
            *port |= bit; // off by default

            SREG = oldSREG;
        }

        void turnOffPWM() {
            switch(pin) {
                case  3: cbi(TCCR2A, COM2B1); break;
                case  5: cbi(TCCR0A, COM0B1); break;
                case  6: cbi(TCCR0A, COM0A1); break;
                case  9: cbi(TCCR1A, COM1A1); break;
                case 10: cbi(TCCR1A, COM1B1); break;
                case 11: cbi(TCCR2A, COM2A1); break;
            }
        }

        void on() {
            /* turnOffPWM(); */

            uint8_t oldSREG = SREG;
            cli();

            *port |= bit;

            SREG = oldSREG;
        }

        void off() {
            /* turnOffPWM(); */

            uint8_t oldSREG = SREG;
            cli();

            *port &= ~bit;

            SREG = oldSREG;
        }
};
