#include<stdio.h>
#include<ctype.h>
#include<string.h>

char word[50][20];

void getparagraph(char* sentence, int length);
void countWords(const char *sentence);
void sortWords(char words[][20], int counts[], int wordCount);
void swapInts(int *a, int *b);
void swapStrings(char *a, char *b);

int main(){
    char paragraph[1000];
    getparagraph(paragraph, 1000);
    
    countWords(paragraph);
    return 0;
}


void getparagraph(char* sentence, int length){
    fgets(sentence, length, stdin);
    size_t len = strlen(sentence);
    if (len>0 && sentence[len-1]=='\n')
        sentence[len-1] = '\0';
}

void countWords(const char *sentence) {
    if (strlen(sentence) == 0) {
        printf("句子为空，无法统计。\n");
        return;
    }
    
    char words[50][20]; 
    int counts[50] = {0}; 
    int wordCount = 0;                    
    
    char tempSentence[1000];
    strcpy(tempSentence, sentence);
    
    
    int i = 0;
    int sentenceLength = strlen(tempSentence);
    
    while (i < sentenceLength) {
        
        while (i < sentenceLength && (isspace(tempSentence[i]) || ispunct(tempSentence[i]))) {
            i++;
        }
        
        if (i >= sentenceLength) {
            break;
        }
        
        int wordStart = i;
        while (i < sentenceLength && !(isspace(tempSentence[i]) || ispunct(tempSentence[i]))) {
            i++;
        }
        
        char currentWord[20];
        int wordLength = i - wordStart;
        
        if (wordLength > 0 && wordLength < 20) {
            strncpy(currentWord, tempSentence + wordStart, wordLength);
            currentWord[wordLength] = '\0';
            
            for (int i=0; i< sizeof(currentWord)/sizeof(char); i++){
                currentWord[i] = tolower(currentWord[i]);
            }
            
    
            bool found = false;
            for (int j = 0; j < wordCount; j++) {
                if (strcmp(words[j], currentWord) == 0) {
                    counts[j]++;
                    found = true;
                    break;
                }
            }
            

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
            printf("%5s(%d) ", words[j], counts[j]);
        }
        
        printf("\nwords Found: %d", wordCount);
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