//Author: Denis Ragan

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char swap(char);
void print_error_message(int);

int check_length(char* input){
    if (strlen(input) == 100 && input[99] != '\n'){
        print_error_message(4);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int check_input_data(char* input){
    for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
        if(!(isdigit(input[i])) && input[i] != '+'){
            print_error_message(3);
            return EXIT_FAILURE;
            }
}
    return EXIT_SUCCESS;
}

void print_error_message(int error){
    switch(error){
        case 1:
            fprintf(stderr, "Invalid input data\n");
            break;
        case 2:
            fprintf(stderr,"Too many arguments\n");
            break;
        case 3:
            fprintf(stderr,"Invalid input data format\n");
            break;
        case 4:
            fprintf(stderr,"Too many characters in a string\n");
            break;
        default:
            break;
    }
}

void print(char name[], char tel_num[], bool *printed){
    printf("%s, %s\n", name, tel_num);
    *printed = true;
}

char* cycle_b4_swap(char* num_name, char* name){
    int name_counter = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if(isalpha(name[i]) || name[i] == '+' || name[i] == ' '){
            num_name[name_counter] = swap(name[i]);
            name_counter++;
        }
    }
    num_name[name_counter] = '\0';
    return num_name;
}

char swap(char character){
    switch (tolower(character)) {
        case 'a':
        case 'b':
        case 'c':
            return '2';
        case 'd':
        case 'e':
        case 'f':
            return '3';
        case 'g':
        case 'h':
        case 'i':
            return '4';
        case 'j':
        case 'k':
        case 'l':
            return '5';
        case 'm':
        case 'n':
        case 'o':
            return '6';
        case 'p':
        case 'q':
        case 'r':
        case 's':
            return '7';
        case 't':
        case 'u':
        case 'v':
            return '8';
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return '9';
        case '+':
            return '0';
        default:
            return ' ';
    }
}

int load_lines(char *name, char *tel_num, bool *printed, int argc, char* const argv[]){
    /*
     * Loads two lines from stdin, checks their length, checks
     * if they're in valid format and removes \n operators at
     * the end of the both lines.
     */
    while (fgets(name, 100, stdin) != NULL) {
        if(check_length(name) == EXIT_FAILURE)
            return EXIT_FAILURE;
        name[strcspn(name, "\n")] = 0;
        if (fgets(tel_num, 100, stdin) != NULL) {
            if(check_length(tel_num) == EXIT_FAILURE || check_input_data(tel_num) == EXIT_FAILURE)
                return EXIT_FAILURE;
            tel_num[strcspn(tel_num, "\n")] = 0;
        } else {
            print_error_message(1);
            return EXIT_FAILURE;
        }
        // Prints contacts if there's not an argument.
        if ((argc == 2 && strcmp(argv[argc-1],"-s") == 0) || (argc == 1)) {
            print(name, tel_num, printed);
            /*
             * Mandatory part -
             * Swaps name into its number variation.
             * Finds substring in a string.
             */
        } else if (argc == 2 && strcmp(argv[argc-1],"-s") != 0){
            if (strstr(tel_num, argv[argc-1]) != NULL){
                print(name, tel_num, printed);
            } else {
                char num_name[100];
                cycle_b4_swap(num_name, name);
                if (strstr(num_name, argv[argc-1]) != NULL){
                    print(name, tel_num, printed);
                }
            }
            /*
             * Optional part - when -s argument is added.
             */
        } else {
            char num_name[100];
            int input_counter = 0;
            cycle_b4_swap(num_name, name);
            for (int i = 0; num_name[i] != '\0'; i++) {
                if (num_name[i] == ' ')
                    input_counter = 0;
                if(num_name[i] == argv[argc-1][input_counter]){
                    input_counter++;
                }
                if (argv[argc-1][input_counter] == '\0'){
                    print(name, tel_num, printed);
                    break;
                }
            }
            if (argv[argc-1][input_counter] == '\0'){
                continue;
            }else
                input_counter = 0;
            for (int i = 0; tel_num[i] != '\0'; i++) {
                if(tel_num[i] == argv[argc-1][input_counter]){
                    input_counter++;
                }
                if (argv[argc-1][input_counter] == '\0'){
                    print(name, tel_num, printed);
                    break;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

int main(int argc, char* const argv[]) {
    char name[100];
    char tel_num[100];
    bool printed = false;
    if (argc > 3 || ((argc == 3) && strcmp(argv[argc-2],"-s") != 0)){
        print_error_message(2);
        return EXIT_FAILURE;
    }
    // Checks if phone number(or input argument) is valid.
    if (argc == 3 || (argc == 2 && strcmp(argv[argc-1],"-s") != 0)){
        if(check_input_data(argv[argc-1])== EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    if(load_lines(name, tel_num, &printed, argc, argv) ==  EXIT_FAILURE)
        return EXIT_FAILURE;
    if (!printed){
        printf("Not found\n");
    }
    return EXIT_SUCCESS;
}
