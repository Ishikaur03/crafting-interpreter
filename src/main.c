#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *read_file_contents(const char *filename);

enum Token
{
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    STAR,
    DOT,
    PLUS,
    MINUS,
    SEMICOLON,
    SLASH,
    EQUAL,
    EQUAL_EQUAL,
    BANG,
    BANG_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    STRING,

};

// Add this structure and initialization before the main tokenize logic
struct KeywordMap {
    char* word;
    char* type;
} keywords[] = {
    {"and", "AND"},
    {"class", "CLASS"},
    {"else", "ELSE"},
    {"false", "FALSE"},
    {"for", "FOR"},
    {"fun", "FUN"},
    {"if", "IF"},
    {"nil", "NIL"},
    {"or", "OR"},
    {"print", "PRINT"},
    {"return", "RETURN"},
    {"super", "SUPER"},
    {"this", "THIS"},
    {"true", "TRUE"},
    {"var", "VAR"},
    {"while", "WHILE"}
};

// Add this function before the main tokenize logic
char* check_keyword(char* word) {
    int keywords_size = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < keywords_size; i++) {
        if (strcmp(word, keywords[i].word) == 0) {
            return keywords[i].type;
        }
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3)
    {
        fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "tokenize") == 0)
    {
        // You can use print statements as follows for debugging, they'll be visible when running tests.
        // fprintf(stderr, "Logs from your program will appear here!\n");

        char *file_contents = read_file_contents(argv[2]);
        char *filePtr = file_contents;

        long int currentLine = 1;

        int error = 0;
        if (strlen(file_contents) > 0)
        {
            // fprintf(stderr, "Scanner not implemented\n");
            // exit(1);
            for (int i = 0; i < strlen(file_contents); i++)
            {
                switch (file_contents[i])
                {
                case '(':
                {
                    printf("LEFT_PAREN ( null\n");
                    break;
                }
                case ')':
                {
                    printf("RIGHT_PAREN ) null\n");
                    break;
                }
                case '{':
                {
                    printf("LEFT_BRACE { null\n");
                    break;
                }
                case '}':
                {
                    printf("RIGHT_BRACE } null\n");
                    break;
                }
                case '.':
                {
                    printf("DOT . null\n");
                    break;
                }
                case '*':
                {
                    printf("STAR * null\n");
                    break;
                }
                case '-':
                {
                    printf("MINUS - null\n");
                    break;
                }
                case '+':
                {
                    printf("PLUS + null\n");
                    break;
                }
                case '/':
                {
                    if (file_contents[i + 1] == '/')
                    {
                        while (i < strlen(file_contents) && file_contents[i] != '\n')
                        {
                            i++;
                        }
                        if (i < strlen(file_contents) && file_contents[i] == '\n')
                        {
                            currentLine++;
                        }
                    }
                    else
                        printf("SLASH / null\n");
                    break;
                }
                case ';':
                {
                    printf("SEMICOLON ; null\n");
                    break;
                }
                case ',':
                {
                    printf("COMMA , null\n");
                    break;
                }
                case '=':
                {
                    if (file_contents[i + 1] == '=')
                    {
                        printf("EQUAL_EQUAL == null\n");
                        i++;
                    }
                    else
                        printf("EQUAL = null\n");
                    break;
                }
                case '!':
                {
                    if (file_contents[i + 1] == '=')
                    {
                        printf("BANG_EQUAL != null\n");
                        i++;
                    }
                    else
                        printf("BANG ! null\n");
                    break;
                }
                case '<':
                {
                    if (file_contents[i + 1] == '=')
                    {
                        printf("LESS_EQUAL <= null\n");
                        i++;
                    }
                    else
                        printf("LESS < null\n");
                    break;
                }
                case '>':
                {
                    if (file_contents[i + 1] == '=')
                    {
                        printf("GREATER_EQUAL >= null\n");
                        i++;
                    }
                    else
                        printf("GREATER > null\n");
                    break;
                }

                case '"':
                {

                    int start = ++i; // Move past the opening quote
                    while (i < strlen(file_contents) && file_contents[i] != '"')
                    {
                        i++;
                    }

                    if (i >= strlen(file_contents))
                    {
                        // Unterminated string error
                        fprintf(stderr, "[line %lld] Error: Unterminated string.\n", currentLine);
                        error = 1;
                        break;
                    }

                    int length = i - start;
                    char str[length + 1];
                    strncpy(str, &file_contents[start], length);
                    str[length] = '\0'; // Null-terminate the string

                    printf("STRING \"%s\" %s\n", str, str);
                    break;
                }
                case ' ':
                {
                    break;
                }
                case '\t':
                {
                    break;
                }

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    int is_decimal = 0;
                    int start = i;
                    while (i < strlen(file_contents) && (isdigit(file_contents[i])) || (file_contents[i] == '.'))
                    {
                        if (file_contents[i] == '.')
                        {
                            if (is_decimal)
                            {
                                // If a second '.' is found, stop parsing
                                break;
                            }
                            is_decimal = 1;
                        }
                        i++;
                    }
                    int length = i - start;
                    char *number = malloc(length + 1);

                    strncpy(number, &file_contents[start], length);
                    number[length] = '\0';

                    // Check if the number is decimal or integer
                    if (is_decimal)
                    {
                        char *original_number = strndup(&file_contents[start], length);

                        int j = length - 1;
                        while (j > 0 && number[j] == '0')
                        {
                            j--;
                        }

                        // If the last character is '.', add '0' to make it a valid decimal
                        if (number[j] == '.')
                        {
                            number[j + 1] = '0';
                            number[j + 2] = '\0';
                        }
                        else
                        {
                            number[j + 1] = '\0';
                        }

                        // }
                        printf("NUMBER %s %s\n", original_number, number);
                        free(original_number);
                    }
                    else
                    {
                        printf("NUMBER %s %s.0\n", number, number); // Add .0 for non-decimals
                    }

                    free(number);
                    i--; // Adjust index since the loop increments `i`
                    break;
                }
                /*case '_':
                case 'a' ... 'z':
                case 'A' ... 'Z':
                {
                    int size = 1;
                    for (int j = i + 1; j < strlen(file_contents) + 1; ++j)
                    {
                        if (file_contents[j] == '_' ||
                            (file_contents[j] >= 'a' && file_contents[j] <= 'z') ||
                            (file_contents[j] >= 'A' && file_contents[j] <= 'Z') ||
                            (file_contents[j] >= '0' && file_contents[j] <= '9'))
                        {
                            continue;
                        }
                        else
                        {
                            size = j - i;
                            break;
                        }
                    }
                    char *string = malloc(size);
                    memcpy(string, &file_contents[i], size);
                    fprintf(stdout, "IDENTIFIER ");
                    for (int j = 0; j < size; ++j)
                    {
                        fprintf(stdout, "%c", string[j]);
                    }
                    fprintf(stdout, " null\n");
                    i += size - 1;
                    break;
                }*/
               // Then replace the identifier case with this:
case '_':
case 'a' ... 'z':
case 'A' ... 'Z':
{
    int size = 1;
    for (int j = i + 1; j < strlen(file_contents) + 1; ++j)
    {
        if (file_contents[j] == '_' ||
            (file_contents[j] >= 'a' && file_contents[j] <= 'z') ||
            (file_contents[j] >= 'A' && file_contents[j] <= 'Z') ||
            (file_contents[j] >= '0' && file_contents[j] <= '9'))
        {
            continue;
        }
        else
        {
            size = j - i;
            break;
        }
    }
    char *string = malloc(size + 1);  // Add 1 for null terminator
    memcpy(string, &file_contents[i], size);
    string[size] = '\0';  // Null terminate the string

    char* keyword_type = check_keyword(string);
    if (keyword_type != NULL) {
        printf("%s %s null\n", keyword_type, string);
    } else {
        printf("IDENTIFIER %s null\n", string);
    }

    free(string);
    i += size - 1;
    break;
}


                

                case '\n':
                {
                    currentLine += 1;
                    break;
                }
                default:
                {
                    fprintf(stderr, "[line %lld] Error: Unexpected character: %c\n", currentLine, file_contents[i]);
                    error = 1;
                }
                }
            }
        }
        printf("EOF  null\n"); // Placeholder, remove this line when implementing the scanner

        free(file_contents);
        if (error)
        {
            exit(65);
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    return 0;
}

char *read_file_contents(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_contents = malloc(file_size + 1);
    if (file_contents == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read < file_size)
    {
        fprintf(stderr, "Error reading file contents\n");
        free(file_contents);
        fclose(file);
        return NULL;
    }

    file_contents[file_size] = '\0';
    fclose(file);

    return file_contents;
}
