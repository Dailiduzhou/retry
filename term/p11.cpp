#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Word {
    char word[80];
    unsigned count;
    Word* next;
} Word;

Word* create_node(char* word, unsigned count){
    Word* new_node = (Word *)malloc(sizeof(Word));
    if (!new_node){
        exit(1);
    }
    strncpy(new_node->word, word, sizeof(new_node->word)-1);
    new_node->count = 1;
    new_node->next =NULL;
    return new_node;
}

void insert_node(Word** head, Word* new_node){
    if (*head == NULL){
        *head = new_node;
    } else {
        Word* current = *head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_node;
    }
}

void search_word(Word* head, char* word){
    Word* current = head;
    while (current != NULL){
        if (strcmp(current->word, word) == 0){
            current->count += 1;
        }
        current = current->next;
    }
}

void swap_data(Word* a, Word* b){
    char temp_word[80];
    strcpy(temp_word, a->word);
    strcpy(a->word, b->word);
    strcpy(b->word, temp_word);
    
    // 交换count
    unsigned temp_count = a->count;
    a->count = b->count;
    b->count = temp_count;
}
void sort_list(Word* head){
    Word* current = head;
    
    int swapped;
    Word *last = NULL;

    do {
        swapped = 0;
        current = head;

        while (current->next != last) {
            if (current->count < current->next->count) {
                swap_data(current, current->next);
                swapped = 1;
            } else if (current->count == current->next->count && strcmp(current->word, current->next->word) > 0){
                swap_data(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

int main(){
    Word * head = NULL;
    char line[1001];
    fgets(line, 1000, stdin);

    int len = strlen(line);
    if (line[len-1] == '\n') {
        line[len-1] = '\0';
    }

    char* copy = (char*)malloc(strlen(line) + 1);
    strcpy(copy, line);
    
    char* token = strtok(copy, " ");
    while (token != NULL) {
        Word* current = head;
        int found = 0;
        while (current != NULL) {
            if (strcmp(current->word, token) == 0) {
                current->count += 1;
                found = 1;
                break;
            }
            current = current->next;
        }
        
        if (!found) {
            Word* new_node = create_node(token, 1);
            insert_node(&head, new_node);
        }
        
        token = strtok(NULL, " ");
    }
    
    free(copy);
    
    sort_list(head);
    
    Word* current = head;
    while (current != NULL) {
        printf("%s %u\n", current->word, current->count);
        current = current->next;
    }
    
    return 0;
}
