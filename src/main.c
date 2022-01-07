// Sample code for ECE 198

// Inialization written by Bernie Roehl, August 2021
// All other code-- unless specified written by Henry 

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:

#define MORSE_CODE

#include <stdbool.h>  // booleans, i.e. true and false
#include <stdio.h>    // sprintf() function

#include "ece198.h"

// this is a flatened binary tree with n being the index
// increasing n by 2 will traverse it's left branch while 2n+1 will traverse
// it's right please see this image of an unflattened version of the tree
// https://en.wikipedia.org/wiki/Morse_code#/media/File:Morse_code_tree3.png
uint16_t n = 1;
const char* letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";

int main(void) {
    HAL_Init();  // initialize the Hardware Abstraction Layer
    // Peripherals (including GPIOs) are disabled by default to save power, so
    // we use the Reset and Clock Control registers to enable the GPIO
    // peripherals that we're using.
    __HAL_RCC_GPIOA_CLK_ENABLE();  // enable port A (for the on-board LED, for
                                   // example)
    __HAL_RCC_GPIOB_CLK_ENABLE();  // enable port B (for the rotary encoder
                                   // inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE();  // enable port C (for the on-board blue
                                   // pushbutton, for example)
    // initialize the pins to be input, output, alternate function, etc...
    InitializePin(GPIOA, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,
                  0);  // on-board LED
    // note: the on-board pushbutton is fine with the default values (no
    // internal pull-up resistor is required, since there's one on the board)
    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e.
    // serial monitor) in VSCode)
    SerialSetup(9600);
    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has
    // been uncommented)

    // used to track the difference in time between button presses
    uint64_t t1 = 0, t2 = 0;
    // to set the time unit for morse code
    // print morse code to output explaining to set a time unit hold the button
    while (debounce1()) {
    }
    t1 = HAL_GetTick();
    while (debounce2()) {
    }
    t2 = HAL_GetTick();
    uint32_t ut = t2 - t1;
    SerialPuts(ut);
    // this is currently commented out as for testing/prototyping purposes 333
    // ms is a lot more reasonable of a time than something like 50ms

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
            // question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut) shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut)) longPress();
                // if the time difference is an enter (accounting for human
                // error)
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
                if ((t2 - t1 > 10 * ut)) resetPress();
            }
        }

        // second question
        question2();
        // loop to check button state
        while (state) {
            // question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut) shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut)) longPress();
                // if the time difference is an enter (accounting for human
                // error)
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
                if ((t2 - t1 > 10 * ut)) resetPress();
            }
        }

        // third question
        question3();
        // loop to check button state
        while (state) {
            // question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut) shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut)) longPress();
                // if the time difference is an enter (accounting for human
                // error)
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
                if ((t2 - t1 > 10 * ut)) resetPress();
            }
        }

        // fourth question
        question4();
        // loop to check button state
        while (state) {
            // question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut) shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut)) longPress();
                // if the time difference is an enter (accounting for human
                // error)
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
                if ((t2 - t1 > 10 * ut)) resetPress();
            }
        }

        // fifth question
        question5();
        // loop to check button state
        while (state) {
            // question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut) shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut)) longPress();
                // if the time difference is an enter (accounting for human
                // error)
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
                if ((t2 - t1 > 10 * ut)) resetPress();
            }
        }

        // sixth question
        question6();
        // loop to check button state
        while (state) {
            // question output
            if (debounce1()) {
                // find when the button was pressed
                t1 = HAL_GetTick();
            }
            if (debounce2()) {
                // find when it was released and for how long
                t2 = HAL_GetTick();
                // if the time difference is a dit (accounting for human error)
                if ((t2 - t1) < 1.5 * ut) shortPress();
                // if the time difference is a dash (accounting for human error)
                if (((t2 - t1) > 2 * ut) && ((t2 - t1) < 4 * ut)) longPress();
                // if the time difference is an enter (accounting for human
                // error)
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
                if ((t2 - t1 > 10 * ut)) resetPress();
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
    // shifts in the state of the button and applies a mask to ignore the bits
    // from the left
    state = (state << 1) | HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) | 0xfe00;
    // once the button has stopped jumping 8 times in a row, it will return true
    return (state == 0xff00);
}

bool debounce2() {
    // tracks the state of the variable
    static uint16_t state = 0;
    // shifts in the state of the button and applies a mask to ignore the bits
    // from the left
    state = (state << 1) | !HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) | 0xfe00;
    // once the button has stopped jumping 8 times in a row, it will return true
    return (state == 0xff00);
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void) {
    HAL_IncTick();  // tell HAL that a new tick has happened
                    // we can do other things in here too if we need to, but be
                    // careful
}

// written by Jinha Kim, September 2021
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

//
void question1() {
    char str[] = "hi!";
    for (int i = 0; str[i] != '\0'; ++i) {
        printMorse(str[i]);
    }
}

void question2() {
    char str[] = "hi!";
    for (int i = 0; str[i] != '\0'; ++i) {
        printMorse(str[i]);
    }
}

void question3() {
    char str[] = "hi!";
    for (int i = 0; str[i] != '\0'; ++i) {
        printMorse(str[i]);
    }
}

void question4() {
    char str[] = "hi!";
    for (int i = 0; str[i] != '\0'; ++i) {
        printMorse(str[i]);
    }
}

void question5() {
    char str[] = "hi!";
    for (int i = 0; str[i] != '\0'; ++i) {
        printMorse(str[i]);
    }
}

void question6() {
    char str[] = "hi!";
    for (int i = 0; str[i] != '\0'; ++i) {
        printMorse(str[i]);
    }
}

void question7() {
    char str[] = "hi!";
    for (int i = 0; str[i] != '\0'; ++i) {
        printMorse(str[i]);
    }
}
