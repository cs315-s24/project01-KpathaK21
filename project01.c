#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 



uint32_t string_to_int(char *str, int base) {
    uint32_t retval = 0;
    uint32_t placeval = 1;

    int length = strlen(str);

    // Check for binary prefix "0b" or "0B"
    if ((base == 2 || base == 10) && length >= 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
        str += 2; // Skip "0b" or "0B" prefix
        length -= 2;
        base = 2; // Set the base to binary
    }

    for (int i = length - 1; i >= 0; i--) {
            int digitValue;
    
            // Convert character to integer
            if (str[i] >= '0' && str[i] <= '9') {
                digitValue = str[i] - '0';
            } else if (base == 16 && ((str[i] >= 'A' && str[i] <= 'F') || (str[i] >= 'a' && str[i] <= 'f'))) {
                digitValue = str[i] - (str[i] >= 'a' ? 'a' : 'A') + 10;
            } else {
                // Handle invalid character
                fprintf(stderr, "Bad input\n");
                exit(EXIT_FAILURE);
            }

            // Update retval based on the digit at the current place
                    retval += digitValue * placeval;
            
                    // Update placeval for the next iteration
                    placeval *= base;
                }
            
                return retval;
            }


void int_to_string(uint32_t value, char *str, int base) {
    char buffer[32]; // Assuming a 32-bit integer, adjust accordingly
    int index = 0;

    // Handle special case when value is 0
    if (value == 0) {
        buffer[index++] = '0';
    }

    while (value != 0) {
        uint32_t quot = value / base;
        uint32_t rem = value % base;

        // Convert remainder to character
                char digitChar;
                if (rem < 10) {
                    digitChar = rem + '0';
                } else {
                    digitChar = rem - 10 + 'A';
                }
        
                // Append character to the buffer
                buffer[index++] = digitChar;
        
                // Update value for the next iteration
                value = quot;
            }

            // Copy buffer into str in reverse order
                for (int i = 0; i < index; i++) {
                    str[i] = buffer[index - 1 - i];
                }
            
                // Null-terminate the string
                str[index] = '\0';
            }








            
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <number> -o <output_base>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *number = argv[1];
    int outputBase = 0;

    if (strcmp(argv[3], "2") == 0) {
        outputBase = 2;
    } else if (strcmp(argv[3], "10") == 0) {
        outputBase = 10;
    } else if (strcmp(argv[3], "16") == 0) {
        outputBase = 16;
    } else {
        printf("Invalid output base\n");
        return EXIT_FAILURE;
    }
     uint32_t result = string_to_int(number, outputBase);
     
         if (outputBase == 2) {
             char binaryStr[33]; // Assuming a 32-bit integer and null terminator
             int_to_string(result, binaryStr, 2);
             printf("0b%s\n", binaryStr);
         } else if (outputBase == 16) {
             char hexStr[9]; // Assuming a 32-bit integer and null terminator
             int_to_string(result, hexStr, 16);
             printf("0x%s\n", hexStr);
         }
     
         return EXIT_SUCCESS;
}
