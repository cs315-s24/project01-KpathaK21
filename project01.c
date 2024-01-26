#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

uint32_t string_to_int(char *str, int base);
void int_to_string(uint32_t value, char *str, int base);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <number> -o <output_base>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int outputBase = atoi(argv[3]);

    if (outputBase != 2 && outputBase != 10 && outputBase != 16) {
        printf("Invalid output base. Use 2, 10, or 16.\n");
        return 1;
    }

    uint32_t decimalValue = string_to_int(input, (outputBase == 16) ? 16 : 10);

    if (decimalValue == UINT32_MAX) {
        printf("Bad input\n");
        return 1;
    }

    char output[33];  // Assuming 32-bit numbers
        int_to_string(decimalValue, output, outputBase);
    
        if (outputBase == 2) {
            printf("0b%s\n", output);
        } else if (outputBase == 10) {
            printf("%s\n", output);
        } else if (outputBase == 16) {
            printf("0x%s\n", output);
        }
    
        return 0;
    }


uint32_t string_to_int(char *str) {
        
            uint32_t result = 0;
            int sign = 1; // Initialize the sign to positive
        
            // Handle leading '+' or '-' signs
            if (*str == '-') {
                sign = -1;
                str++;
            } else if (*str == '+') {
                str++;
            }
        
            // Iterate through the string and convert each character to an integer
            while (*str) {
                char digit = *str;
                int value = 0;
        
                if (digit >= '0' && digit <= '9') {
                    value = digit - '0';
                } else {
                    // Invalid character
                    return 0;
                }
        
                result = result * 10 + value;
                str++;
            }
        
            return result * sign; 
        }
    }

    void int_to_string(uint32_t value, char *str, int base) {
        if (base < 2 || base > 16) {
        return;
    }

    int num_digits = 1;
    uint32_t temp_value = value;

    int total_length = 0;

    while (temp_value /= base) {
        num_digits++;
    }

    if (base == 2) {
        total_length = 32;
    } else if (base == 16) {
        total_length = 8;
    }

    int i = 0;
    int sign = 0;

     do {
        int digit = value % base; // for absolute value
        str[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        value /= base;
    } while (value > 0);

    // add padding
    while (i < total_length) {
        str[i++] = '0';
    }

    // Add 0x for hex and 0b for binary
    if (base == 2) {
        str[i++] = 'b';
        str[i++] = '0';
    } else if (base == 16) {
        str[i++] = 'x';
        str[i++] = '0';
    }

    str[i] = '\0';
    
        // Reverse the string
        int start = 0;
        int end = i - 1;
        while (start < end) {
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start++;
            end--;
        }

         // Handle sign for hex representation
    if (base == 16 && sign == -1) {
        int length = i;
        for (int j = length; j >= 0; j--) {
            str[j + 1] = str[j];
        }
        str[0] = '-';
    }
       
        }
