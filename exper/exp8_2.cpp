#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h> // 【修复1】必须包含这个头文件才能用 bool


void getparagraph(char* sentence, int length);
void countWords(const char *sentence);
void sortWords(char words[][20], int counts[], int wordCount);
void swapInts(int *a, int *b);
void swapStrings(char *a, char *b);

int main(){
    char paragraph[1000];
    // 提示用户输入，体验更好
    printf("请输入段落: "); 
    getparagraph(paragraph, 1000);
    
    countWords(paragraph);
    return 0;
}

void getparagraph(char* sentence, int length){
    if (fgets(sentence, length, stdin) != NULL) {
        size_t len = strlen(sentence);
        if (len > 0 && sentence[len-1] == '\n')
            sentence[len-1] = '\0';
    }
}

void countWords(const char *sentence) {
    if (sentence == NULL || strlen(sentence) == 0) {
        printf("句子为空，无法统计。\n");
        return;
    }
    
    char words[50][20]; 
    int counts[50] = {0}; 
    int wordCount = 0;                    
    
    // 注意：如果 sentence 非常长，tempSentence 可能会溢出。
    // 生产环境中建议使用动态分配或检查长度。
    char tempSentence[1000]; 
    strncpy(tempSentence, sentence, sizeof(tempSentence) - 1);
    tempSentence[sizeof(tempSentence) - 1] = '\0'; // 确保截断后安全
    
    int i = 0;
    int sentenceLength = strlen(tempSentence);
    
    while (i < sentenceLength) {
        // 跳过标点和空格
        while (i < sentenceLength && (isspace(tempSentence[i]) || ispunct(tempSentence[i]))) {
            i++;
        }
        
        if (i >= sentenceLength) {
            break;
        }
        
        int wordStart = i;
        // 找到单词结尾
        while (i < sentenceLength && !(isspace(tempSentence[i]) || ispunct(tempSentence[i]))) {
            i++;
        }
        
        char currentWord[20];
        int wordLength = i - wordStart;
        
        // 限制单词长度防止溢出，留一个字节给 '\0'
        if (wordLength > 19) wordLength = 19; 

        if (wordLength > 0) {
            // 复制单词
            strncpy(currentWord, tempSentence + wordStart, wordLength);
            currentWord[wordLength] = '\0'; // 关键：手动封口
            
            // 【修复2】只转换有效长度的字符
            for (int k = 0; k < wordLength; k++){
                currentWord[k] = tolower(currentWord[k]);
            }
            
            // 查找是否已存在
            bool found = false;
            for (int j = 0; j < wordCount; j++) {
                if (strcmp(words[j], currentWord) == 0) {
                    counts[j]++;
                    found = true;
                    break;
                }
            }
            
            // 插入新单词
            if (!found && wordCount < 50) {
                strcpy(words[wordCount], currentWord);
                counts[wordCount] = 1;
                wordCount++;
            }
        }
    }
    
    sortWords(words, counts, wordCount);

    if (wordCount == 0) {
        printf("未找到有效的单词。\n");
    } else {
        for (int j = 0; j < wordCount; j++) {
            // 格式优化：%-10s 表示左对齐，看起来更整齐
            printf("%-10s(%d) ", words[j], counts[j]);
            // 每5个单词换一行，防止太长
            if ((j + 1) % 5 == 0) printf("\n");
        }
        printf("\n\nWords Found: %d\n", wordCount);
    }
}

void swapStrings(char *a, char *b) {
    char temp[20];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void swapInts(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortWords(char words[][20], int counts[], int wordCount) {
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - i - 1; j++) {
            // 逻辑：频率不同按频率降序；频率相同按字典序升序
            if (counts[j] < counts[j + 1]) {
                swapStrings(words[j], words[j + 1]);
                swapInts(&counts[j], &counts[j + 1]);
            }
            else if (counts[j] == counts[j + 1]) {
                if (strcmp(words[j], words[j + 1]) > 0) {
                    swapStrings(words[j], words[j + 1]);
                    swapInts(&counts[j], &counts[j + 1]);
                }
            }
        }
    }
}