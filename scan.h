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
                        // If the input starts with '0b', check for binary numbers
                            if (number[0] == '0' && (number[1] == 'b' || number[1] == 'B')) {
                                // Check if the rest of the string contains only '0' and '1'
                                for (int i = 2; number[i] != '\0'; i++) {
                                    if (number[i] != '0' && number[i] != '1') {
                                        char* result = (char*)malloc(12); // Assuming 11 characters for "bad input" + null terminator
                                        strcpy(result, "bad input");
                                        return result;
                                    }
                                }
                            }

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

        
