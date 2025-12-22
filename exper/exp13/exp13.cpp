#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RECORDS 1000
#define MAX_LINE_LEN 256
#define DATE_LEN 11
#define TIME_LEN 9

typedef struct {
    char date[DATE_LEN];
    char caller[32]; 
    char callee[32];     
    char start_time[TIME_LEN];
    int duration;    
    float cost;          
} TELLBILL;

void ReadRelBill(TELLBILL *p, int *n);
void ShowTelBill(TELLBILL *p);
int TelType(char *p);
float CalTelFee(char *pcalled, int sec);
void SortTelBill(TELLBILL *p, int n);
void DisplayAllBills(TELLBILL *p, int n);
void RemoveNewline(char *str);

int main() {
    TELLBILL records[MAX_RECORDS];
    int record_count = 0;
    
    ReadRelBill(records, &record_count);
    
    SortTelBill(records, record_count);
    
    printf("\n通话记录（按话费从高到低排序）：\n");
    DisplayAllBills(records, record_count);
    
    
    return 0;
}

void ReadRelBill(TELLBILL *p, int *n) {
    FILE *input_file;
    char line[MAX_LINE_LEN];
    *n = 0;
    
    input_file = fopen("call_records.txt", "r");
    if (input_file == NULL) {
        printf("无法打开输入文件 call_records.txt！\n");
        return;
    }
    
    
    while (*n < MAX_RECORDS && fgets(line, sizeof(line), input_file) != NULL) {
        RemoveNewline(line);
        
        if (strlen(line) == 0) continue;
        
        char date[11], caller[32], callee[32], time[9];
        int duration;
    
        if (sscanf(line, "%10s %31s %31s %8s %d", 
                   date, caller, callee, time, &duration) == 5) {
            
            strcpy(p[*n].date, date);
            strcpy(p[*n].caller, caller);
            strcpy(p[*n].callee, callee);
            strcpy(p[*n].start_time, time);
            p[*n].duration = duration;
            
            p[*n].cost = CalTelFee(p[*n].callee, duration);            
            (*n)++;
        } else {
            printf("警告: 无法解析行: %s\n", line);
        }
    }
    
    fclose(input_file);
}

void ShowTelBill(TELLBILL *p) {
    printf("%s  %-12s  %-14s  %8s  %11d      ¥%6.2f\n",
           p->date,
           p->caller,
           p->callee,
           p->start_time,
           p->duration,
           p->cost);
}

void DisplayAllBills(TELLBILL *p, int n) {
    printf("日期        主叫号码        被叫号码          起始时间   通话时长(秒)   话费(元)\n");
    
    
    for (int i = 0; i < n; i++) {
        ShowTelBill(&p[i]);
    }
    
    printf("总计: %d 条记录\n", n);
}

int TelType(char *p) {
    while (*p == ' ') p++;
    
    if (strncmp(p, "00", 2) == 0) {
        return 1; 
    }
    else if (p[0] == '0' && p[1] != '0') {
        return 2;
    }
    else if (strncmp(p, "101", 3) == 0) {
        return 2;
    }
    else {
        return 3;
    }
}

float CalTelFee(char *pcalled, int sec) {
    int minutes = (sec + 59) / 60;
    int tel_type = TelType(pcalled);
    float cost = 0.0;
    
    switch (tel_type) {
        case 1:
            cost = minutes * 1.00;
            break;
        case 2: 
            cost = minutes * 0.60;
            break;
        case 3:
            if (sec <= 180) {
                cost = 0.20;
            } else {
                int extra_seconds = sec - 180;
                int extra_minutes = (extra_seconds + 59) / 60;
                cost = 0.20 + extra_minutes * 0.10;
            }
            break;
    }
    
    return cost;
}

int compare_by_cost(const void *a, const void *b) {
    const TELLBILL *record_a = (const TELLBILL *)a;
    const TELLBILL *record_b = (const TELLBILL *)b;
    
    if (record_b->cost > record_a->cost) return 1;
    if (record_b->cost < record_a->cost) return -1;
    return 0;
}

void SortTelBill(TELLBILL *p, int n) {
    qsort(p, n, sizeof(TELLBILL), compare_by_cost);
}

void RemoveNewline(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
}