/* main.c */
#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTING 0

void write_part(char *str, int len, int uppercase);

void write_standard_password(char *buffer, int len, int pts);

void write_random_password(char *buffer, int len);

void write_random_pin(char *buffer, int len);

void print_commands();

/* use for testing */
#if TESTING
int rand() { return 1000; }
#endif

/*       number of args                                       */
/*             |                                              */
/*             |  pointer to vector of pointers to args       */
/*             |            |                                 */
int main(int argc, const char **argv) {
#if !TESTING
    srand(time(0));
    char buffer[61]; /* max password length is 60 */

    if (argc > 1) {
        if (strcmp(argv[1], "word") == 0) {
            write_standard_password(buffer, 20, 3);
        } else if (strcmp(argv[1], "random") == 0) {
            write_random_password(buffer, 15);
        } else if (strcmp(argv[1], "pin") == 0) {
            write_random_pin(buffer, 4);
        } else if (strcmp(argv[1], "help") == 0) {
            printf("Pgen is a tool for generating passwords.\n");
            print_commands();
            return 0;
        } else {
            for (int i = 0; i < argc; i++) {
                printf("%s", argv[i]);
                if (i < argc - 1)
                    printf(" ");
            }
            printf(": unknown command\n");
            print_commands();
            return 0;
        }
    } else {
        write_standard_password(buffer, 20, 3);
    }
    printf("%s", buffer);

    /* copy to clipboard using pbcopy */
    FILE *pipe = popen("pbcopy", "w");
    if (pipe != NULL) {
        int err = fprintf(pipe, "%s", buffer);
        if (err < 0)
            printf(" [NOT COPIED]");
        else
            printf(" [COPIED]");
        pclose(pipe);
    }
    printf("\n");
#endif

/* Test write_standard_password */
/* NOTE: - Set rand function to 1000. */
#if TESTING
    char buffer[60]; /* allow variable length, but max is 60 */

    write_standard_password(buffer, 20, 3);
    printf("len 20 pts 3: %s\n",
           strcmp(buffer, "bababa-bababa-8ABABA") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 19, 3);
    printf("len 19 pts 3: %s\n",
           strcmp(buffer, "bababa-bababa-8ABAB") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 18, 3);
    printf("len 18 pts 3: %s\n",
           strcmp(buffer, "bababa-babab-8ABAB") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 17, 3);
    printf("len 17 pts 3: %s\n",
           strcmp(buffer, "babab-babab-8ABAB") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 16, 3);
    printf("len 16 pts 3: %s\n",
           strcmp(buffer, "babab-babab-8ABA") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 15, 3);
    printf("len 15 pts 3: %s\n",
           strcmp(buffer, "babab-baba-8ABA") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 14, 3);
    printf("len 14 pts 3: %s\n",
           strcmp(buffer, "baba-baba-8ABA") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 13, 3);
    printf("len 13 pts 3: %s\n",
           strcmp(buffer, "baba-baba-8AB") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 12, 3);
    printf("len 12 pts 3: %s\n",
           strcmp(buffer, "baba-bab-8AB") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 11, 3);
    printf("len 11 pts 3: %s\n",
           strcmp(buffer, "bab-bab-8AB") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 10, 3);
    printf("len 10 pts 3: %s\n",
           strcmp(buffer, "bab-bab-8A") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 9, 3);
    printf("len 9 pts 3: %s\n", strcmp(buffer, "bab-ba-8A") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 8, 3);
    printf("len 8 pts 3: %s\n", strcmp(buffer, "ba-ba-8A") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 7, 3);
    printf("len 7 pts 3: %s\n", strcmp(buffer, "ba-ba-8") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 6, 3);
    printf("len 6 pts 3: %s\n", strcmp(buffer, "ba-b-8") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 5, 3);
    printf("len 5 pts 3: %s\n", strcmp(buffer, "b-b-8") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 4, 3);
    printf("len 4 pts 3: %s\n", strcmp(buffer, "b-b-") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 3, 3);
    printf("len 3 pts 3: %s\n", strcmp(buffer, "b--") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 2, 3);
    printf("len 2 pts 3: %s\n", strcmp(buffer, "--") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 1, 3);
    printf("len 1 pts 3: %s\n", strcmp(buffer, "-") == 0 ? "ok" : "fail");

    write_standard_password(buffer, 0, 3);
    printf("len 0 pts 3: %s\n", strcmp(buffer, "") == 0 ? "ok" : "fail");
#endif
    return 0;
}

/* writes fake word password to buffer */
void write_standard_password(char *buffer, int len, int pts) {
    /* TODO: - Rewrite. */
    int chr_pt = (len - (pts - 1)) / pts;        /* find part length */
    int msng = len - (chr_pt * pts + (pts - 1)); /* find missing chars */

    int uppercase_used = 0;
    int uppercase = 0;

    int number_used = 0;
    int saved_i = 0;
    int chr_pt_num = chr_pt;

    int i = 0;
    while (i < len) {
        chr_pt_num = chr_pt;
        uppercase = 0;
        if (!uppercase_used) {
            if (i >= len - chr_pt) {
                uppercase = 1;
                uppercase_used = 1;
            } else {
                uppercase = rand() % 2;
                if (uppercase)
                    uppercase_used = 1;
            }
        }
        if (msng > 0) {
            write_part(&buffer[i], chr_pt + 2, uppercase);
            saved_i = i;
            chr_pt_num = chr_pt + 1;
            i += chr_pt + 1;
            msng--;
        } else {
            write_part(&buffer[i], chr_pt + 1, uppercase);
            saved_i = i;
            i += chr_pt;
        }
        if (!number_used) {
            if (i >= len - chr_pt) {
                first_to_number(&buffer[saved_i], chr_pt_num);
                number_used = 1;
            } else {
                if (rand() % 2) {
                    first_to_number(&buffer[saved_i], chr_pt_num);
                    number_used = 1;
                }
            }
        }
        if (i < len) {
            buffer[i] = '-';
            i++;
        }
    }
    buffer[len] = '\0';
}

/* writes random password to buffer */
void write_random_password(char *buffer, int len) {
    for (int i = 0; i < len; i++) {
        char character;
        if (rand() % 2) {
            character = random_uppercase_letter();
        } else if (rand() % 2) {
            character = random_number();
        } else {
            character = random_lowercase_letter();
        }
        buffer[i] = character;
    }
    buffer[len] = '\0';
}

/* writes random pin to buffer */
void write_random_pin(char *buffer, int len) {
    for (int i = 0; i < len; i++) {
        buffer[i] = random_number();
    }
    buffer[len] = '\0';
}

/* writes a non-existent word to buffer */
void write_part(char *buffer, int len, int uppercase) {
    for (int i = 0; i < (len - 2); i += 2) {
        buffer[i] = random_consonant(uppercase);
        buffer[i + 1] = random_vowel(uppercase);
    }
    if ((len - 1) % 2 != 0)
        buffer[len - 2] = random_consonant(uppercase);
    buffer[len] = '\0';
}

/* print commands info */
void print_commands() {
    printf("\nUsage:\n");
    printf("        pgen <command>\n");
    printf("\nThe commands are:\n");
    printf("        word      non-existent words (default)\n");
    printf("        random    random characters\n");
    printf("        pin       four digit pin\n");
}
