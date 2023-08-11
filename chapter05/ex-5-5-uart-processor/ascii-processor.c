#include "uart-processor.h"
/*
 * This ascii processor converts
 * - Upper case (A-Z) character to lower case.
 * - Lower case (a-z) character to upper case.
 * - Non-Alphabetic characters are returned as-is.
 */
int process_input(int data) {

    if (data >= 65 && data <= 90) {
        // Upper case characters
        return data + 32;
    } else if (data >= 97 && data <= 122) {
        // Lower case characters
        return data - 32;
    }
    return data;
}