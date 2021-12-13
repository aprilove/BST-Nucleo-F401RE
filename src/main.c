// Sample code for ECE 198

// Written by Bernie Roehl, August 2021

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:

#define MORSE_CODE

#include <stdbool.h>  // booleans, i.e. true and false
#include <stdio.h>    // sprintf() function

#include "ece198.h"

// this is a flatened binary tree with n being the index
// increasing n by 2 will traverse it's left branch while 2n+1 will traverse it's right
// please see this image of an unflattened version of the tree
// https://en.wikipedia.org/wiki/Morse_code#/media/File:Morse_code_tree3.png
uint16_t n = 1;
const char* letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";

// this is the time unit for a dit in morse code (also simply known as a time unit)
// there is code to allow ut to be readjustable as seen on line 51 - 62 but
// the user inputted time unit is often inaccurate (whether due to human error or code is unknown)
uint32_t ut = 333;

int main(void) {
    HAL_Init();  // initialize the Hardware Abstraction Layer
    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.
    __HAL_RCC_GPIOA_CLK_ENABLE();  // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE();  // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE();  // enable port C (for the on-board blue pushbutton, for example)
    // initialize the pins to be input, output, alternate function, etc...
    InitializePin(GPIOA, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED
    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)
    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)
    SerialSetup(9600);
    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

    // used to track the difference in time between button presses
    uint64_t t1 = 0, t2 = 0;

    // to set the time unit for morse code
    // print morse code to output explaining to set a time unit hold the button
    // while (debounce1()) {
    // }
    // t1 = HAL_GetTick();
    // while (debounce2()) {
    // }
    // t2 = HAL_GetTick();
    // uint32_t ut = t2-t1;
    // SerialPuts(ut);
    // this is currently commented out as for testing/prototyping purposes 333 ms
    // is a lot more reasonabale of a time than something like 50ms

    // to continuously loop the process
    while (1) {
        // to track whether a question has been answered with yes
        bool state = true;
        // to track the time between when the button was pressed and released
        t1 = 0;
        t2 = 0;
        // first question
        question1();
        // loop to check button state
        while (state) {
            //question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut)
                    shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut))
                    longPress();
                // if the time difference is an enter (accounting for human error)
                if ((t2 - t1 > 5 * ut) && (t2 - t1 < 7 * ut)) {
                    // determine if button pressed was Y or N
                    // else ask the question again
                    if (letter[n] == 'Y') {
                        break;
                    } else if (letter[n] == 'N') {
                        state = false;
                        break;
                    } else {
                        question1();
                    }
                    veryLongPress();
                }
                // to reset in case you made a mistake
                if ((t2 - t1 > 10 * ut))
                    resetPress();
            }
        }

        // second question
        question2();
        // loop to check button state
        while (state) {
            //question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut)
                    shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut))
                    longPress();
                // if the time difference is an enter (accounting for human error)
                if ((t2 - t1 > 5 * ut) && (t2 - t1 < 7 * ut)) {
                    // determine if button pressed was Y or N
                    // else ask the question again
                    if (letter[n] == 'Y') {
                        break;
                    } else if (letter[n] == 'N') {
                        state = false;
                        break;
                    } else {
                        question2();
                    }
                    veryLongPress();
                }
                // to reset in case you made a mistake
                if ((t2 - t1 > 10 * ut))
                    resetPress();
            }
        }

        // third question
        question3();
        // loop to check button state
        while (state) {
            //question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut)
                    shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut))
                    longPress();
                // if the time difference is an enter (accounting for human error)
                if ((t2 - t1 > 5 * ut) && (t2 - t1 < 7 * ut)) {
                    // determine if button pressed was Y or N
                    // else ask the question again
                    if (letter[n] == 'Y') {
                        break;
                    } else if (letter[n] == 'N') {
                        state = false;
                        break;
                    } else {
                        question3();
                    }
                    veryLongPress();
                }
                // to reset in case you made a mistake
                if ((t2 - t1 > 10 * ut))
                    resetPress();
            }
        }

        // fourth question
        question4();
        // loop to check button state
        while (state) {
            //question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut)
                    shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut))
                    longPress();
                // if the time difference is an enter (accounting for human error)
                if ((t2 - t1 > 5 * ut) && (t2 - t1 < 7 * ut)) {
                    // determine if button pressed was Y or N
                    // else ask the question again
                    if (letter[n] == 'Y') {
                        break;
                    } else if (letter[n] == 'N') {
                        state = false;
                        break;
                    } else {
                        question4();
                    }
                    veryLongPress();
                }
                // to reset in case you made a mistake
                if ((t2 - t1 > 10 * ut))
                    resetPress();
            }
        }

        // fifth question
        question5();
        // loop to check button state
        while (state) {
            //question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut)
                    shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut))
                    longPress();
                // if the time difference is an enter (accounting for human error)
                if ((t2 - t1 > 5 * ut) && (t2 - t1 < 7 * ut)) {
                    // determine if button pressed was Y or N
                    // else ask the question again
                    if (letter[n] == 'Y') {
                        break;
                    } else if (letter[n] == 'N') {
                        state = false;
                        break;
                    } else {
                        question5();
                    }
                    veryLongPress();
                }
                // to reset in case you made a mistake
                if ((t2 - t1 > 10 * ut))
                    resetPress();
            }
        }

        // sixth question
        question6();
        // loop to check button state
        while (state) {
            //question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut)
                    shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut))
                    longPress();
                // if the time difference is an enter (accounting for human error)
                if ((t2 - t1 > 5 * ut) && (t2 - t1 < 7 * ut)) {
                    // determine if button pressed was Y or N
                    // else ask the question again
                    if (letter[n] == 'Y') {
                        break;
                    } else if (letter[n] == 'N') {
                        state = false;
                        break;
                    } else {
                        question6();
                    }
                    veryLongPress();
                }
                // to reset in case you made a mistake
                if ((t2 - t1 > 10 * ut))
                    resetPress();
            }
        }

        // conclusion of results
        if (state) {
            // output safe
            printMorse('Y');
            printMorse('O');
            printMorse('U');

            printMorse('A');
            printMorse('R');
            printMorse('E');

            printMorse('G');
            printMorse('O');
            printMorse('O');
            printMorse('D');

            printMorse('T');
            printMorse('O');

            printMorse('G');
            printMorse('O');
        } else {
            // not safe, contact staff
            printMorse('P');
            printMorse('L');
            printMorse('E');
            printMorse('A');
            printMorse('S');
            printMorse('E');

            printMorse('C');
            printMorse('O');
            printMorse('N');
            printMorse('T');
            printMorse('A');
            printMorse('C');
            printMorse('T');

            printMorse('S');
            printMorse('T');
            printMorse('A');
            printMorse('F');
            printMorse('F');

            printMorse('A');
            printMorse('S');
            printMorse('A');
            printMorse('P');
        }

        // delay before asking questions again
        HAL_Delay(10000);
    }
    return 0;
}

void longPress() {
    // increments the index to traverse the right branch
    n = 2 * n + 1;
    // to determine what was just pressed (strictly for testing purposes)
    SerialPutc(n + '0');
}

void shortPress() {
    // increments the index to traverse the left branch
    n *= 2;
    // to determine what was just pressed (strictly for testing purposes)
    SerialPutc(n + '0');
}

void veryLongPress() {
    // outputing the pressed morse code (stictly for testing purposes)
    printMorse(letter[n] + '0');
    // reset after each question
    resetPress();
}

void resetPress() {
    // resetting the index
    n = 1;
}

bool debounce1() {
    // tracks the state of the variable
    static uint16_t state = 0;
    // shifts in the state of the button and applies a mask to ignore the bits from the left
    state = (state << 1) | HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) | 0xfe00;
    // once the button has stopped jumping 8 times in a row, it will return true
    return (state == 0xff00);
}

bool debounce2() {
    // tracks the state of the variable
    static uint16_t state = 0;
    // shifts in the state of the button and applies a mask to ignore the bits from the left
    state = (state << 1) | !HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) | 0xfe00;
    // once the button has stopped jumping 8 times in a row, it will return true
    return (state == 0xff00);
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void) {
    HAL_IncTick();  // tell HAL that a new tick has happened
                    // we can do other things in here too if we need to, but be careful
}

// transmits the morse code to the LED
char printMorse(char let) {
    // a switch to check which letter was inputted
    switch (let) {
        case 'A':  //* -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            SerialPutc('a');
            break;
        case 'B':  //- ***
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            SerialPutc('b');
            break;
        case 'C':  //- * - *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('c');
            break;
        case 'D':  //- **
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('d');
            break;
        case 'E':  //*
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('e');
            break;
        case 'F':  //**-*
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('f');
            break;
        case 'G':  //- - *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('g');
            break;
        case 'H':  // * * * *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('h');
            break;
        case 'I':  //* *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('i');
            break;
        case 'J':  //* - - -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('j');
            break;
        case 'K':  //- * -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            SerialPutc('k');
            break;
        case 'L':  //* - * *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('l');
            break;
        case 'M':  //- -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            SerialPutc('m');
            break;
        case 'N':  //- *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('n');
            break;
        case 'O':  //- - -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('o');
            break;
        case 'P':  //* - - *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('p');
            break;
        case 'Q':  //- - * -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('q');
            break;
        case 'R':  //* - *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('r');
            break;
        case 'S':  //***
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('s');
            break;
        case 'T':  //-
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('t');
            break;
        case 'U':  //**-
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('u');
            break;
        case 'V':  //***-

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('v');
            break;
        case 'W':  //* - -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('w');
            break;
        case 'X':  //- ** -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('x');
            break;
        case 'Y':  //- * - -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('y');
            break;
        case 'Z':  //- - * *
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('z');
            break;
        case '1':  //* - - - -
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('1');
            break;
        case '2':  // **---
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            SerialPutc('2');
            break;

        case '3':  //***--

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            SerialPutc('3');
            break;

        case '4':  //****-

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            SerialPutc('4');
            break;

        case '5':  //*****
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('5');
            break;

        case '6':  //-****
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('6');
            break;

        case '7':  //--***
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('7');
            break;

        case '8':  //---**
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);

            SerialPutc('8');
            break;

        case '9':  //----*
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

            HAL_Delay(ut);
            SerialPutc('9');
            break;

        case '0':  //-----
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(3 * ut);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
            HAL_Delay(ut);
            SerialPutc('0');
            break;
    }
}

// outputs question 1
void question1() {
    printMorse('D');
    printMorse('O');

    printMorse('Y');
    printMorse('O');
    printMorse('U');

    printMorse('H');
    printMorse('A');
    printMorse('V');
    printMorse('E');

    printMorse('A');
    printMorse('N');
    printMorse('Y');

    printMorse('O');
    printMorse('F');

    printMorse('T');
    printMorse('H');
    printMorse('E');

    printMorse('F');
    printMorse('O');
    printMorse('L');
    printMorse('L');
    printMorse('O');
    printMorse('W');
    printMorse('I');
    printMorse('N');
    printMorse('G');

    printMorse('S');
    printMorse('Y');
    printMorse('M');
    printMorse('P');
    printMorse('T');
    printMorse('O');
    printMorse('M');
    printMorse('S');

    printMorse('F');
    printMorse('E');
    printMorse('V');
    printMorse('E');
    printMorse('R');

    printMorse('T');
    printMorse('I');
    printMorse('R');
    printMorse('E');
    printMorse('D');
    printMorse('N');
    printMorse('E');
    printMorse('S');
    printMorse('S');

    printMorse('S');
    printMorse('O');
    printMorse('R');
    printMorse('E');

    printMorse('T');
    printMorse('H');
    printMorse('R');
    printMorse('O');
    printMorse('A');
    printMorse('T');

    printMorse('M');
    printMorse('U');
    printMorse('S');
    printMorse('C');
    printMorse('L');
    printMorse('E');

    printMorse('P');
    printMorse('A');
    printMorse('I');
    printMorse('N');

    printMorse('N');
    printMorse('A');
    printMorse('U');
    printMorse('S');
    printMorse('E');
    printMorse('A');
}

// outputs question 2
void question2() {
    printMorse('H');
    printMorse('A');
    printMorse('V');
    printMorse('E');

    printMorse('Y');
    printMorse('O');
    printMorse('U');

    printMorse('T');
    printMorse('R');
    printMorse('A');
    printMorse('V');
    printMorse('E');
    printMorse('L');
    printMorse('L');
    printMorse('E');
    printMorse('D');

    printMorse('O');
    printMorse('U');
    printMorse('T');
    printMorse('S');
    printMorse('I');
    printMorse('D');
    printMorse('E');

    printMorse('O');
    printMorse('F');

    printMorse('C');
    printMorse('A');
    printMorse('N');
    printMorse('A');
    printMorse('D');
    printMorse('A');

    printMorse('I');
    printMorse('N');

    printMorse('T');
    printMorse('H');
    printMorse('E');

    printMorse('P');
    printMorse('A');
    printMorse('S');
    printMorse('T');

    printMorse('2');

    printMorse('W');
    printMorse('E');
    printMorse('E');
    printMorse('K');
    printMorse('S');

    printMorse('A');
    printMorse('N');
    printMorse('D');

    printMorse('B');
    printMorse('E');
    printMorse('E');
    printMorse('N');

    printMorse('A');
    printMorse('D');
    printMorse('V');
    printMorse('I');
    printMorse('S');
    printMorse('E');
    printMorse('D');

    printMorse('T');
    printMorse('O');

    printMorse('Q');
    printMorse('U');
    printMorse('A');
    printMorse('R');
    printMorse('A');
    printMorse('N');
    printMorse('T');
    printMorse('I');
    printMorse('N');
    printMorse('E');
}

// outputs question 3
void question3() {
    printMorse('I');
    printMorse('N');

    printMorse('T');
    printMorse('H');
    printMorse('E');

    printMorse('L');
    printMorse('A');
    printMorse('S');
    printMorse('T');

    printMorse('1');
    printMorse('0');

    printMorse('D');
    printMorse('A');
    printMorse('Y');
    printMorse('S');

    printMorse('H');
    printMorse('A');
    printMorse('V');
    printMorse('E');

    printMorse('Y');
    printMorse('O');
    printMorse('U');

    printMorse('B');
    printMorse('E');
    printMorse('E');
    printMorse('N');

    printMorse('I');
    printMorse('N');

    printMorse('C');
    printMorse('O');
    printMorse('N');
    printMorse('T');
    printMorse('A');
    printMorse('C');
    printMorse('T');

    printMorse('W');
    printMorse('I');
    printMorse('T');
    printMorse('H');

    printMorse('A');
    printMorse('N');
    printMorse('Y');
    printMorse('O');
    printMorse('N');
    printMorse('E');

    printMorse('W');
    printMorse('I');
    printMorse('T');
    printMorse('H');

    printMorse('C');
    printMorse('O');
    printMorse('V');
    printMorse('I');
    printMorse('D');
}

// outputs question 4
void question4() {
    printMorse('A');
    printMorse('R');
    printMorse('E');

    printMorse('Y');
    printMorse('O');
    printMorse('U');

    printMorse('S');
    printMorse('U');
    printMorse('P');
    printMorse('P');
    printMorse('O');
    printMorse('S');
    printMorse('E');
    printMorse('D');

    printMorse('T');
    printMorse('O');

    printMorse('B');
    printMorse('E');

    printMorse('S');
    printMorse('E');
    printMorse('L');
    printMorse('F');

    printMorse('I');
    printMorse('S');
    printMorse('O');
    printMorse('L');
    printMorse('A');
    printMorse('T');
    printMorse('I');
    printMorse('N');
    printMorse('G');
}

// outputs question 5
void question5() {
    printMorse('I');
    printMorse('N');

    printMorse('T');
    printMorse('H');
    printMorse('E');

    printMorse('L');
    printMorse('A');
    printMorse('S');
    printMorse('T');

    printMorse('2');

    printMorse('W');
    printMorse('E');
    printMorse('E');
    printMorse('K');
    printMorse('S');

    printMorse('H');
    printMorse('A');
    printMorse('V');
    printMorse('E');

    printMorse('Y');
    printMorse('O');
    printMorse('U');

    printMorse('R');
    printMorse('E');
    printMorse('C');
    printMorse('E');
    printMorse('I');
    printMorse('V');
    printMorse('E');
    printMorse('D');

    printMorse('A');

    printMorse('C');
    printMorse('O');
    printMorse('V');
    printMorse('I');
    printMorse('D');

    printMorse('E');
    printMorse('X');
    printMorse('P');
    printMorse('O');
    printMorse('S');
    printMorse('U');
    printMorse('R');
    printMorse('E');

    printMorse('N');
    printMorse('O');
    printMorse('T');
    printMorse('I');
    printMorse('F');
    printMorse('I');
    printMorse('C');
    printMorse('A');
    printMorse('T');
    printMorse('I');
    printMorse('O');
    printMorse('N');

    printMorse('O');
    printMorse('N');

    printMorse('A');
    printMorse('N');
    printMorse('Y');

    printMorse('D');
    printMorse('E');
    printMorse('V');
    printMorse('I');
    printMorse('C');
    printMorse('E');
}

// outputs question 6
void question6() {
    printMorse('I');
    printMorse('F');

    printMorse('Y');
    printMorse('O');
    printMorse('U');

    printMorse('A');
    printMorse('N');
    printMorse('S');
    printMorse('W');
    printMorse('E');
    printMorse('R');
    printMorse('E');
    printMorse('D');

    printMorse('Y');
    printMorse('E');
    printMorse('S');

    printMorse('T');
    printMorse('O');

    printMorse('A');
    printMorse('N');
    printMorse('Y');

    printMorse('O');
    printMorse('F');

    printMorse('T');
    printMorse('H');
    printMorse('E');
    printMorse('S');
    printMorse('E');

    printMorse('Q');
    printMorse('U');
    printMorse('E');
    printMorse('S');
    printMorse('T');
    printMorse('I');
    printMorse('O');
    printMorse('N');
    printMorse('S');

    printMorse('P');
    printMorse('L');
    printMorse('E');
    printMorse('A');
    printMorse('S');
    printMorse('E');

    printMorse('G');
    printMorse('I');
    printMorse('V');
    printMorse('E');

    printMorse('U');
    printMorse('S');

    printMorse('Y');
    printMorse('O');
    printMorse('U');
    printMorse('R');

    printMorse('R');
    printMorse('O');
    printMorse('O');
    printMorse('M');

    printMorse('N');
    printMorse('U');
    printMorse('M');
    printMorse('B');
    printMorse('E');
    printMorse('R');
}