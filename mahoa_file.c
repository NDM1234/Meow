#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mahoa.h"
#define Alphabet_len 33


int meowso_file(char* input_str, char *file_path, int i, int *cur_out_len, int max_len) {
    char so[3]={0};
    int count;
    if ((i>0 && input_str[i-1]=='-')|| input_str[i]=='.' ) first='M';
    else first='m';
    if(input_str[i]=='.') i++;
    so[0] = input_str[i];
    int next_index=i+1; 
    if(input_str[next_index]>='0' && input_str[next_index]<='9'){
        so[1] = input_str[next_index];
        next_index++;
    }
    else{
        so[1]='\0';
    }
    int c = atoi(so)+33;
    int e_add = c / 9;
    int o_add = (c % 9) / 3;
    int w_add = c % 3;

    char temp[64];
    int offset=0;
    temp[offset++] = first;
    for (int k = 0; k <= e_add; k++) temp[offset++] = 'e';
    for (int k = 0; k <= o_add; k++) temp[offset++] = 'o';
    for (int k = 0; k <= w_add; k++) temp[offset++] = 'w';
    temp[offset++] = '~';
    temp[offset] = '\0';
    FILE *fWrite = fopen(file_path, "a");
    fprintf(fWrite, "%s", temp);
    fclose(fWrite);
    return next_index-1;
}
void meowkitu_file(char *input_str, char *file_path, int i, int *cur_out_len,int max_len){
    char c = input_str[i];
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

    char temp[64];
    int offset=0;
    temp[offset++] = first;
    for (int k = 0; k <= e_add; k++) temp[offset++] = 'e';
    for (int k = 0; k <= o_add; k++) temp[offset++] = 'o';
    for (int k = 0; k <= w_add; k++) temp[offset++] = 'w';
    temp[offset++] = '~';
    temp[offset] = '\0';
    FILE *fWrite = fopen(file_path, "a");
    fprintf(fWrite, "%s", temp);
    fclose(fWrite);
}
void meow_file(char *file_path, char *output_str, int max_len) {
        FILE *fRead = fopen(file_path, "r");
        if (fRead == NULL) {
            snprintf(output_str, max_len, "Khong the mo file.\n");
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
        char out_file_path[1000];
        snprintf(out_file_path, sizeof(out_file_path), "%s_meow.txt", file_path);
        FILE *fWrite = fopen(out_file_path, "w");
        if (fWrite == NULL) {
            snprintf(output_str, max_len, "Khong the mo file de ghi.\n");
            return;
        }
        fclose(fWrite);
        int out_len = 0;
        output_str[0] = '\0';
        for (int i = 0; content[i]!='\0'; i++) {
            if(checkso(content, i)){
                i=meowso_file(content, out_file_path, i, &out_len, max_len);
            }
            if(content[i]>='a' && content[i]<='z' || content[i]>='A' && content[i]<='Z' || content[i]==' ' || content[i]=='!' || content[i]==',' || content[i]=='.' || content[i]=='?' || content[i]=='*'){
                meowkitu_file(content, out_file_path, i, &out_len, max_len);
            }
        }      
        printf("Da ma hoa va luu vao file %s\n", file_path);
}