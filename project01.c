#include "scan.h"


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
