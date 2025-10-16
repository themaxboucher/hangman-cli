#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char* logo = "HANGMAN!";

    printf("Welcome to\n");
    printf("%s\n\n", logo);

    FILE* f = fopen("words.txt", "r");
    if (f == NULL) {
        printf("Error: cannot open the file");
        exit(1);
    }

    // Create an array of strings from the words in the text file
    char** words = NULL; // Array of strings
    int count = 0; // Number of words read
    char buffer[100]; // Temporary ploceholder for words

    while (fscanf(f, "%99s", buffer) == 1) {
        // Allocate memory for a new word
        char* word = malloc(strlen(buffer) + 1); // +1 for '\0'
        if (word == NULL) {
            printf("malloc failed");
            break;
        }
        strcpy(word, buffer);

        // Grow the array of words
        char** temp = realloc(words, (count + 1) * sizeof(char*)); // Temporary pointer to prevent memory leaks
        if (temp == NULL) {
            printf("realloc failed");
            free(word);
            break;
        }
        words = temp;

        // Store the word
        words[count] = word;
        count++;
    }

    fclose(f);

    // Print all words
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }
    free(words);

    return 0;
}