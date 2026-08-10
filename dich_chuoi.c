#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mahoa.h" 
#define Alphabet_len 33

void dichkitu_chuoi(char *word, char *output_str, int *cur_out_len, int max_len){
        if(word[0]=='m'||word[0]=='M'){
        int e=0, o=0, w=0;
        int i=1;
        char temp[64];
        int offset=0;
        while(word[i]=='e'){e++; i++;}
        while(word[i]=='o'){o++; i++;}
        while(word[i]=='w'){w++; i++;}
        int index= (e-1)*9+(o-1)*3+(w-1);
        if(index>=0 && index<Alphabet_len){
            if(word[0]=='M') temp[offset++] = 'A'+index;
            else temp[offset++] = ALPHABET[index];
        }
        else temp[offset++] = ALPHABET[32];
        temp[offset] = '\0';
        if(*cur_out_len + strlen(temp) < max_len){
            strcat(output_str+*cur_out_len, temp);
            *cur_out_len += strlen(temp);
        }
    }
}
void dichso_chuoi(char *word, char *output_str, int *cur_out_len, int max_len){
    char so[50]={0};
    char *p=word;
    int so_dau=1;
    int da_in_dau_cham=0;
    while(*p!='\0'){
        int idx=0;
        while(*p!='~' && *p!='\0'){
            so[idx++]=*p;
            p++;
        }
        so[idx]='\0';
        if(*p=='~') p++;
        if(so[0]=='m'||so[0]=='M'){
            char temp[64];
            int offset=0;
            if(so[0]=='M'&& so_dau==1){
                temp[offset++] = '-';
                temp[offset] = '\0';
            }
            int so_thuc = (so[0] == 'M' && so_dau == 0 && da_in_dau_cham == 0) ? 1 : 0;
            int e=0,o=0,w=0;
            int i=1;
            while(so[i]=='e'){e++; i++;}
            while(so[i]=='o'){o++; i++;}
            while(so[i]=='w'){w++; i++;}
            int index= (e-1)*9+(o-1)*3+(w-1)-33;
            if(so_thuc){
                temp[offset++] = '.';
                da_in_dau_cham=1;
            }
            offset += sprintf(temp + offset, "%d", index);
            temp[offset] = '\0';
            if(*cur_out_len + strlen(temp) < max_len){
                strcat(output_str+*cur_out_len, temp);
                *cur_out_len += strlen(temp);
            }
        }
        so_dau=0;
    }
}
void dichphu_chuoi(char *input_str, char *output_str, int *cur_out_len, int max_len){
    char *p=input_str;
    while(*p!='\0'){
        while(*p==' ' || *p=='\n' || *p=='\r' ){
            p++;
        }
        if(*p=='\0') break;
        char word[200]={0};
        int idx=0;
        while(*p!=' ' && *p!='\n' && *p!='\r' && *p!='\0'){
            word[idx++]=*p;
            p++;
        }
        int count=0;
        for(int i=0;i<idx;i++){
            if(word[i]=='~') count=1;
        }
        if(count==1){
            dichso_chuoi(word, output_str, cur_out_len, max_len);
        }
        else{
            dichkitu_chuoi(word, output_str, cur_out_len, max_len);
        }
    }
}
void dich_chuoi(char *input_str, char *output_str, int max_len){
    int cur_out_len = 0;
    output_str[0] = '\0';
    dichphu_chuoi(input_str ,output_str, &cur_out_len, max_len);
}
