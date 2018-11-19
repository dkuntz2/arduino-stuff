baud=115200
avrType=atmega328p
avrFreq=16000000
programmerDev=/dev/tty.usbmodem141320
programmerType=arduino

cflags=-DF_CPU=$(avrFreq) -mmcu=$(avrType) -Wall -Werror -Wextra -Os -I../lib
objects=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

.PHONY: flash clean

all: main.hex

%.o: %.cpp
	avr-g++ $(cflags) -c $< -o $@

main.elf: $(objects)
	avr-g++ $(cflags) -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

flash: main.hex
	avrdude -p$(avrType) -c$(programmerType) -P$(programmerDev) -b$(baud) -v -U flash:w:$<

clean:
	rm -f main.hex main.elf $(objects)
