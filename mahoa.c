#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mahoa.h"
#define Alphabet_len 33
char first='m';
const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz !?,.*";

int meowso(char *str, int n, int i){
    char so[3]={0};
    int count;
    if ((i>0 && str[i-1]=='-')|| str[i]=='.' ) first='M';
    else first='m';
    if(str[i]=='.') i++;
    so[0] = str[i];
    int next_index=i+1;
    if(str[next_index]>='0' && str[next_index]<='9'){
        so[1] = str[next_index];
        next_index++;
    }
    else{
        so[1]='\0';
    }
    int c = atoi(so)+33;
    int e_add = c / 9;
    int o_add = (c % 9) / 3;
    int w_add = c % 3;
    if(n==1){
        printf("%c", first);
        for (int k = 0; k <= e_add; k++) printf("e");
        for (int k = 0; k <= o_add; k++) printf("o");
        for (int k = 0; k <= w_add; k++) printf("w");
        printf("~");
    }
    else{
        FILE *fWrite = fopen(str, "a");
        fprintf(fWrite, "%c", first);
        for (int k = 0; k <= e_add; k++) fprintf(fWrite, "e");
        for (int k = 0; k <= o_add; k++) fprintf(fWrite, "o");
        for (int k = 0; k <= w_add; k++) fprintf(fWrite, "w");
        fprintf(fWrite, "~");
        fclose(fWrite);
    }
    return next_index-1;
}
void meowkitu(char *str, int n, int i){
    char c = str[i];
    if(c >= 'A' && c <= 'Z') first='M';
    else first='m';
    int index = -1;
    for (int j = 0; j < Alphabet_len; j++) {
        if (ALPHABET[j] == c || (first == 'M' && ALPHABET[j] == c + 32)) {
            index = j;
            break;
        }
    }   
    if (index == -1) index = 32;
    int e_add = index / 9;
    int o_add = (index % 9) / 3;
    int w_add = index % 3;
    if(n==1){
        printf("%c", first);
        for (int j = 0; j <= e_add; j++) printf("e");
        for (int j = 0; j <= o_add; j++) printf("o");
        for (int j = 0; j <= w_add; j++) printf("w");
        printf(" "); 
    }
    else{
        FILE *fWrite = fopen(str, "a");
        if (fWrite == NULL) {
            printf("Khong the mo file de ghi.\n");
            return;
        }
        fprintf(fWrite, "%c", first);
        for (int k = 0; k <= e_add; k++) fprintf(fWrite, "e");
        for (int k = 0; k <= o_add; k++) fprintf(fWrite, "o");
        for (int k = 0; k <= w_add; k++) fprintf(fWrite, "w");
        fprintf(fWrite, " "); 
        fclose(fWrite);
    }
}
int checkso(char *str, int i){
    if(str[i]>='0' && str[i]<='9'){
        return 1;
    }
    else if((i>0 && str[i-1]=='-') && str[i]>='0' && str[i]<='9'){
        return 1;
    }
    else if(str[i]=='.' && str[i+1]>='0' && str[i+1]<='9' && str[i-1]>='0' && str[i-1]<='9' && i>0){
        return 1;
    }
    return 0;
}
void meow(char *str, int n) {
    if(n==1){
        for (int i = 0; str[i]!= '\0'; i++) {
            //xử lí số
            if(checkso(str, i)){
                i=meowso(str,n,i);
            }
            //xử lí kí tự
            if((str[i]>='a' && str[i]<='z')||(str[i]>='A' && str[i]<='Z')||str[i]==' ' || str[i]=='!' || str[i]==',' || str[i]=='.' || str[i]=='?' || str[i]=='*'){
                meowkitu(str,n,i);
            }
        }
        printf("\n");
        printf("Da ma hoa.\n");
    }
    else{
        FILE *fRead = fopen(str, "r");
        if (fRead == NULL) {
            printf("Khong the mo file.\n");
            return;
        }
        char content[1000];
        int i = 0;
        char c = fgetc(fRead);
        while (c != EOF && i < 999) {
            content[i++] = c;
            c = fgetc(fRead);
        }
        content[i] = '\0';
        fclose(fRead);
        FILE *fWrite = fopen(str, "w");
        if (fWrite == NULL) {
            printf("Khong the mo file de ghi.\n");
            return;
        }
        fclose(fWrite);
        for (int i = 0; content[i]!='\0'; i++) {
            if(checkso(content, i)){
                i=meowso(content,n,i);
            }
            if(content[i]>='a' && content[i]<='z' || content[i]>='A' && content[i]<='Z' || content[i]==' ' || content[i]=='!' || content[i]==',' || content[i]=='.' || content[i]=='?' || content[i]=='*'){
                meowkitu(content,n,i);
            }
        }      
        printf("Da ma hoa va luu vao file %s\n", str);
    }
}