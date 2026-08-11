#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mahoa.h"
#define Alphabet_len 33
char first='m';
const char ALPHABET[] = " abcdefghijklmnopqrstuvwxyz!?,.*";

int meowso_chuoi(char *input_str, char *output_str, int i, int *cur_out_len, int max_len){
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
    if(*cur_out_len + strlen(temp) < max_len){
        strcat(output_str+*cur_out_len, temp);
        *cur_out_len += strlen(temp);
    }
    return next_index-1;
}
void meowkitu_chuoi(char *input_str, char *output_str, int i, int *cur_out_len, int max_len){
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
    temp[offset++] = ' ';
    temp[offset] = '\0';
    if(*cur_out_len + strlen(temp) < max_len){
        strcat(output_str+*cur_out_len, temp);
        *cur_out_len += strlen(temp);
    }
}
void meow_chuoi(char *input_str, char *output_str, int max_len) {
        int out_len = 0;
        output_str[0] = '\0'; // Khởi tạo chuỗi output_str
        for (int i = 0; input_str[i]!= '\0'; i++) {
            //xử lí số
            if(checkso(input_str, i)){
                i=meowso_chuoi(input_str,output_str,i,&out_len,max_len);
            }
            //xử lí kí tự
            if((input_str[i]>='a' && input_str[i]<='z')||(input_str[i]>='A' && input_str[i]<='Z')||input_str[i]==' ' || input_str[i]=='!' || input_str[i]==',' || input_str[i]=='.' || input_str[i]=='?' || input_str[i]=='*'){
                if(out_len > 0 && output_str[out_len-1] != ' ') {
                    output_str[out_len++] = ' ';
                }
                meowkitu_chuoi(input_str,output_str,i,&out_len,max_len);
            }
        }
}