#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

char str1[] = "#include <stdio.h>\n"
              "char str[] = \"";
char str3[] = "\";\n"
              "\n"
              "int main() {\n"
              "    printf(\"%s\", str);\n"
              "}";

int main() {
    FILE *fp;
    fp = fopen("tmp.c", "w");
    if (fp == NULL) {
        printf("Error create tmp.c");
        exit(1);
    }
    fwrite(str1, sizeof(char), strlen(str1), fp);
    char str2[BUFFER_SIZE];
    char escaped_str2[BUFFER_SIZE * 2];
    while (1) {
        size_t n = read(STDIN_FILENO, str2, BUFFER_SIZE);
        if (n == -1) {
            printf("Error read from stdin");
            exit(1);
        }
        if (n == 0) {
            break;
        }
        // n > 0
        int j = 0;
        for (int i = 0; i < n; i++) {
            switch (str2[i]) {
                case '\n':
                    escaped_str2[j++] = '\\';
                    escaped_str2[j++] = 'n';
                    break;
                case '\t':
                    escaped_str2[j++] = '\\';
                    escaped_str2[j++] = 't';
                    break;
                case '\\':
                    escaped_str2[j++] = '\\';
                    escaped_str2[j++] = '\\';
                    break;
                case '"':
                    escaped_str2[j++] = '\\';
                    escaped_str2[j++] = '"';
                    break;
                default:
                    escaped_str2[j++] = str2[i];
                    break;
            }
        }
        fwrite(escaped_str2, sizeof(char), j, fp);
    }
    fwrite(str3, sizeof(char), strlen(str3), fp);
    fclose(fp);
    if (system("gcc tmp.c -o tmp") != 0) {
        printf("Error execute gcc");
        exit(1);
    }
//    remove("tmp.c");
    return 0;
}
