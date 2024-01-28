#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <ctype.h>
// Function to calculate the length of a string
int strLength(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Function to reverse a string
void reverseString(char *str, int length) {
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

// Function to convert a string to an integer
uint32_t string_to_int(const char *str) {
   uint32_t result = 0;
        int length = strLength(str);
    
        // Check if the input starts with a prefix
        int startIdx = 0;
        
       if (length >= 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
        startIdx = 2;

        for (int i = startIdx; i < length; i++) {
            if (str[i] == '0' || str[i] == '1') {
                result = result * 2 + (str[i] - '0');
            } else {
                printf("Bad input\n");
                return 0; // Bad input for binary
            }
        }
    } else if (length >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        startIdx = 2;

        for (int i = startIdx; i < length; i++) {
            if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F')) {
                result = result * 16 + (isdigit(str[i]) ? str[i] - '0' : (tolower(str[i]) - 'a') + 10);
            } else {
               printf("Bad input\n");
                                return 0; // Bad input for hexadecimal
            }
        }
        } else if (length >= 1 && str[0] == '0') {
                startIdx = 1;
        
                for (int i = startIdx; i < length; i++) {
                    if (str[i] >= '0' && str[i] <= '7') {
                        result = result * 8 + (str[i] - '0');
                    } else {
                        printf("Bad input\n");
                                        return 0; // Bad input for octal
                    }
                }
            } else {
                for (int i = startIdx; i < length; i++) {
                    if (str[i] >= '0' && str[i] <= '9') {
                        result = result * 10 + (str[i] - '0');
                    } else {
						 printf("Bad input\n");
                        return 0; // Bad input for decimal
                    }
                }
            }
        
            return result;
}

// Function to convert an integer to a string
void int_to_string(uint32_t value, char *str, int base) {
    int index = 0;

    // Convert the value to the specified base
    do {
        int remainder = value % base;

        if (remainder < 10) {
            str[index++] = remainder + '0';
        } else {
            str[index++] = remainder - 10 + 'a';
        }

        value = value / base;
    } while (value > 0);

    // Reverse the result string
    reverseString(str, index);

    // Null-terminate the string
    str[index] = '\0';
}

// Function to convert a number to the specified base
char* convertBase(const char* number, int base) {

 // Convert the input string to an integer
    uint32_t num = string_to_int(number);

    // Buffer to store the result
    char* result = (char*)malloc(33); // Assuming 32-bit integer, plus one for null terminator
    int index = 0;

    // Check for the output base and format accordingly
    do {
        int remainder = num % base;

        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else if (base == 2) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'a';
        }

        num = num / base;
    } while (num > 0);

    // Add base prefix if it's not 10
        if (base == 2) {
            result[index++] = 'b';
            result[index++] = '0';
        } else if (base == 16) {
            result[index++] = 'x';
            result[index++] = '0';
        }
    
        result[index] = '\0';
    
        // Reverse the result string
        reverseString(result, index);
    
        return result;
        }








  
        int main(int argc, char *argv[]) {
            // Check if the correct number of arguments is provided
            if (argc != 4) {
                printf("Usage: %s <number> -o <base>\n", argv[0]);
                return 1;
            }
        
            // Get the input number and base
            char* number = argv[1];
            char* option = argv[2];
            int base = string_to_int(argv[3]);
        
            // Check if the option is "-o"
            if (strLength(option) != 2 || option[0] != '-' || option[1] != 'o') {
                printf("Invalid option\n");
                return 1;
            }

            // Convert the number to the specified base
                char* result = convertBase(number, base);
            
                // Print the result
                printf("%s\n", result);
            
                // Free allocated memory
                free(result);
            
                return 0;
            }
