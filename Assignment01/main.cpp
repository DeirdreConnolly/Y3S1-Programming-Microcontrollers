#include "mbed.h"
#include "LM75B.h"
#include "C12832.h"

/*
Neither breached    =   green
Lower passed        =   flash orange twice per second, audible alarm sounds
Approaching higher  =   flashing increases to 5 times per second, linear
Higher passed       =   flash red once every 2 seconds, audible alarm sounds
*/

C12832 lcd(p5, p7, p6, p8, p11);    // LCD screen

LM75B sensor(p28, p27);     // Temp sensor = current temp
Serial pc(USBTX, USBRX);

AnalogIn pot1(p19);
AnalogIn pot2(p20);

DigitalOut led1(LED1);  // Built-in LEDs
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

PwmOut r(p23);  // RGB LED pins
PwmOut g(p24);
PwmOut b(p25);

PwmOut speaker(p26);    // PWM speaker for alarm

float valuePot1, valuePot2;
float temp;

Timer t;    // Timer
Ticker tick; // Ticker

void screen() {

    lcd.cls();  // Clear screen
    lcd.locate(0, 3);
    lcd.printf("Higher = %.3f\n", valuePot2);   // Print higher threshold
    lcd.printf("Lower = %.3f\n", valuePot1);    // Print lower threshold
    lcd.printf("Temp = %.3f\n", temp);          // Print current temp
}

void red() {     // Red LED on
    r = 0.0;
    g = 1.0;
    b = 1.0;
}

void green() {   // Green LED on
    r = 1.0;
    g = 0.9;
    b = 1.0;
}

void orange() {    // Orange LED on
    r = 0.95;
    g = 0.95;
    b = 1.0;
}

void off() {     // All LEDs off
    r = 1.0;
    g = 1.0;
    b = 1.0;
}

int main() {

    speaker.period(1.0 / 5000);

    tick.attach(&screen, 1);    // Apply ticker to screen, update every second

    while (1) {     // While true

        temp = sensor.read();

        valuePot1 = (pot1 * 40);   // Read from analog input
        valuePot2 = (pot2 * 40);

        // RED
        if (temp > valuePot2) {    // Temp above higher threshold

            //speaker.period(1.0 / 5000);      // This breaks LEDs
            speaker = 0.5;      // Alarm2 sounds

            t.start();          // Start timer

            if (t.read() >= 2) {    // Get the timer time
                red();              // Turn on red LED
                t.reset();          // Reset LED
            } else {
                off();              // Turn off LEDs
            }

        // ORANGE
        } else if (temp > valuePot1) {  // Temp above lower threshold AND below higher = flash orange

            speaker = 0.5;      // Sound alarm2

            t.start();          // Start timer

            if (t.read() >= 0.5) {  // Get the timer time
                orange();           // Turn on orange LED
                t.reset();          // Reset LED
            } else {
                off();              // Turn off LEDs
            }


        // GREEN
        } else {                    // Temp below lower threshold

            green();                // Turn on green LED
            speaker = 0;
        }
    }
}
