#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[11];
    int maths;
    int english;
    int c;
    int total;
    struct Student *next;
} Student;

Student* create_node(const char *name, int maths, int english, int c) {
    Student *new_node = (Student*)malloc(sizeof(Student));
    if (!new_node) {
        printf("内存分配失败\n");
        exit(1);
    }
    strncpy(new_node->name, name, sizeof(new_node->name) - 1);
    new_node->name[sizeof(new_node->name) - 1] = '\0';
    new_node->maths = maths;
    new_node->english = english;
    new_node->c = c;
    new_node->total = maths + english + c;
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

    char name[11];
    int maths, english, c;

    while (fscanf(file, "%10s %d %d %d", name, &maths, &english, &c) == 4) {
        Student *new_node = create_node(name, maths, english, c);
        insert_node(head, new_node);
    }

    fclose(file);
}

void swap_data(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;

    Student *temp_next = a->next;
    a->next = b->next;
    b->next = temp_next;
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
            if (current->total < current->next->total) {
                swap_data(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void print_list(Student *head) {
    printf("姓名        数学  英语  C语言 总分\n");
    printf("-------------------------------\n");

    Student *current = head;
    while (current != NULL) {
        printf("%-10s %-4d %-4d %-4d %-4d\n",
               current->name, current->maths, current->english, current->c, current->total);
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
    
    char name[11];
    int maths, english, c;
    while (scanf("%10s%d%d%d", name, &maths, &english, &c) == 4) {
        Student* new_node = create_node(name, maths, english, c);
        insert_node(&head, new_node);
    }
    
    sort_list(head);
    
    print_list(head);

    free_list(head);
    
    return 0;
}