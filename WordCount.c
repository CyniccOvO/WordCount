#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// 函数原型
bool is_delimiter(char c);
int count_words(FILE *file);
int count_characters(FILE *file);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] <file_name>\n", argv[0]);
        return 1;
    }

    char *param = argv[1];
    char *filename = argv[2];
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int result = 0;
    if (strcmp(param, "-c") == 0) {
        result = count_characters(file);
        printf("字符数：%d\n", result);
    } else if (strcmp(param, "-w") == 0) {
        result = count_words(file);
        printf("单词数：%d\n", result);
    } else {
        printf("Invalid parameter. Use '-c' for characters or '-w' for words.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

bool is_delimiter(char c) {
    return isspace(c) || c == ',';
}

int count_words(FILE *file) {
    int count = 0;
    bool in_word = false;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (is_delimiter(c)) {
            if (in_word) {
                count++;
                in_word = false;
            }
        } else {
            in_word = true;
        }
    }
    // 检查最后一个单词
    if (in_word) count++;
    return count;
}

int count_characters(FILE *file) {
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}
