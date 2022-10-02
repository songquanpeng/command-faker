#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX(a, b) (((a)>(b))?(a):(b))


char str1[] = "#include <stdio.h>\n"
              "char str[] = \"";
char str3[] = "\";\n"
              "\n"
              "int main() {\n"
              "    printf(\"%s\", str);\n"
              "}";

int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen("tmp.c", "w");
    if (fp == NULL) {
        printf("Error create tmp.c");
        exit(1);
    }
    fwrite(str1, sizeof(char), strlen(str1), fp);
    char buf[BUFFER_SIZE];
    char escaped_str2[BUFFER_SIZE * 2];
    while (1) {
        size_t n = read(STDIN_FILENO, buf, BUFFER_SIZE);
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
            switch (buf[i]) {
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
                    escaped_str2[j++] = buf[i];
                    break;
            }
        }
        fwrite(escaped_str2, sizeof(char), j, fp);
    }
    fwrite(str3, sizeof(char), strlen(str3), fp);
    fclose(fp);
    char cmd[13 + MAX(3, sizeof(argv[1]))] = "gcc tmp.c -o ";
    if (argc == 1) {
        strcat(cmd, "tmp");
    } else {
        strcat(cmd, argv[1]);
    }
    if (system(cmd) != 0) {
        printf("Error execute gcc");
        exit(1);
    }
    remove("tmp.c");
    if (argc == 1) {
        fp = fopen("tmp", "rb");
        if (fp == NULL) {
            printf("Error read tmp");
            exit(1);
        }
        while (1) {
            size_t n = fread(buf, 1, BUFFER_SIZE, fp);
            if (n == -1) {
                printf("Error read from stdin");
                exit(1);
            }
            if (n == 0) {
                break;
            }
            size_t remain = n;
            size_t offset = 0;
            while (remain) {
                size_t n_wrote = write(STDOUT_FILENO, buf + offset, remain);
                if (n_wrote == -1) {
                    printf("Error write to stdout");
                    exit(1);
                }
                remain -= n_wrote;
                offset += n_wrote;
            }
        }
        remove("tmp");
    }
    return 0;
}
