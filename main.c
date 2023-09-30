#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 30

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} LinkedList;

void initializeList(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

void appendToList(LinkedList *list, char *word) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->word = strdup(word);
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void freeList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
}

bool hasRepeatingLetters(const char *word) {
    int seenChars[256] = {0};

    for (const char *ch = word; *ch != '\0'; ch++) {
        if (seenChars[(unsigned char)*ch]) {
            return true;
        }
        seenChars[(unsigned char)*ch] = 1;
    }

    return false;
}

void printWordsWithoutLetterRepetitions(LinkedList *words) {
    Node *current = words->head;
    while (current != NULL) {
        if (!hasRepeatingLetters(current->word)) {
            printf("%s ", current->word);
        }
        current = current->next;
    }
}

int main() {
    FILE *inputFile = fopen("../input.txt", "r");

    if (inputFile == NULL) {
        fprintf(stderr, "Failed to open input file.\n");
        return 1;
    }

    LinkedList wordsList;
    initializeList(&wordsList);

    char word[MAX_WORD_LENGTH];
    int ch;

    while ((ch = fgetc(inputFile)) != EOF) {
        if (isalpha(ch)) {
            strncat(word, (char *)&ch, 1);
        } else if (strlen(word) > 0) {
            appendToList(&wordsList, word);
            word[0] = '\0';
        }
    }

    if (strlen(word) > 0) {
        appendToList(&wordsList, word);
    }

    fclose(inputFile);

    printWordsWithoutLetterRepetitions(&wordsList);

    freeList(&wordsList);

    return 0;
}
