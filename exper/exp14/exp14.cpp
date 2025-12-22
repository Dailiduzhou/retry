#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char id[9];       
    char name[11];    
    int score;     
    int time;         
    struct Student *next; 
} Student;

Student* create_node(char *id, char *name, int score, int time) {
    Student *new_node = (Student*)malloc(sizeof(Student));
    if (!new_node) {
        printf("内存分配失败\n");
        exit(1);
    }
    strcpy(new_node->id, id);
    strcpy(new_node->name, name);
    new_node->score = score;
    new_node->time = time;
    new_node->next = NULL;
    return new_node;
}

void insert_node(Student **head, Student *new_node) {
    if (*head == NULL) {
        *head = new_node;
    } else {
        Student *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void read_from_file(Student **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件: %s\n", filename);
        exit(1);
    }
    
    char id[9], name[11];
    int score, time;
    
    while (fscanf(file, "%8s %10s %d %d", id, name, &score, &time) == 4) {
        Student *new_node = create_node(id, name, score, time);
        insert_node(head, new_node);
    }
    
    fclose(file);
}

void swap_data(Student *a, Student *b) {
    char temp_id[9];
    strcpy(temp_id, a->id);
    strcpy(a->id, b->id);
    strcpy(b->id, temp_id);
    
    char temp_name[11];
    strcpy(temp_name, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, temp_name);

    int temp_score = a->score;
    a->score = b->score;
    b->score = temp_score;

    int temp_time = a->time;
    a->time = b->time;
    b->time = temp_time;
}

void sort_list(Student *head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    int swapped;
    Student *current;
    Student *last = NULL;
    
    do {
        swapped = 0;
        current = head;
        
        while (current->next != last) {
            if (current->score < current->next->score || 
                (current->score == current->next->score && current->time > current->next->time)) {
                swap_data(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void print_list(Student *head) {
    printf("学号     姓名        成绩  时间\n");
    printf("--------------------------------\n");
    
    Student *current = head;
    while (current != NULL) {
        printf("%-8s %-10s %-5d %-5d\n", 
               current->id, current->name, current->score, current->time);
        current = current->next;
    }
}

void free_list(Student *head) {
    Student *current = head;
    while (current != NULL) {
        Student *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Student *head = NULL;
    
    read_from_file(&head, "stumsg.txt");
    
    sort_list(head);
    
    print_list(head);

    free_list(head);
    
    return 0;
}