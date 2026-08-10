#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mahoa.h"
#define Alphabet_len 33

void dichkitu_file(char *word, char *output_str, int max_len){
        if(word[0]=='m'||word[0]=='M'){
        int e=0,o=0,w=0;
        int i=1;
        while(word[i]=='e'){e++; i++;}
        while(word[i]=='o'){o++; i++;}
        while(word[i]=='w'){w++; i++;}
        int index= (e-1)*9+(o-1)*3+(w-1);
        FILE *fWrite = fopen(output_str, "a");
        if (fWrite == NULL) {
            printf("Khong the mo file de ghi.\n");
            return;
        }
        if(index>=0 && index<Alphabet_len){
            if(word[0]=='M') fprintf(fWrite,"%c", 'A'+index);
            else fprintf(fWrite,"%c", ALPHABET[index]);
        }
        else fprintf(fWrite,"%c", ALPHABET[32]);
        fclose(fWrite);
    }
}
void dichso_file(char *word, char *file_path, int max_len){
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
            if(so[0]=='M'&& so_dau==1){
                FILE *fWrite=fopen(file_path, "a");
                if(fWrite!=NULL){
                    fprintf(fWrite, "-");
                    fclose(fWrite);
                }
            }
            int so_thuc = (so[0] == 'M' && so_dau == 0 && da_in_dau_cham == 0) ? 1 : 0;
            int e=0,o=0,w=0;
            int i=1;
            while(so[i]=='e'){e++; i++;}
            while(so[i]=='o'){o++; i++;}
            while(so[i]=='w'){w++; i++;}
            int index= (e-1)*9+(o-1)*3+(w-1)-33;
            FILE *fWrite = fopen(file_path, "a");
            if (fWrite == NULL) {
                printf("Khong the mo file de ghi.\n");
                return;
            }
            if(so_thuc){
                fprintf(fWrite, ".");
                da_in_dau_cham=1;
            }
            fprintf(fWrite, "%d", index);
            fclose(fWrite);
        }
        so_dau=0;
    }
}
void dichphu_file(char *input_str, char *output_str, int max_len){
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
            dichso_file(word, output_str, max_len);
        }
        else{
            dichkitu_file(word, output_str, max_len);
        }
    }
}
void dich_file(char *file_path,char *output_str, int max_len){
        FILE *fRead = fopen(file_path, "r");
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
        char out_file_path[1000];
        snprintf(out_file_path, sizeof(out_file_path), "%s_demeow.txt", file_path);
        FILE *fWrite = fopen(out_file_path, "w");
        if (fWrite == NULL) {
            printf("Khong the mo file de ghi.\n");
            return;
        }
        fclose(fWrite);
        dichphu_file(content, out_file_path, max_len);
        FILE *fFinal=fopen(out_file_path, "a");
        if(fFinal!=NULL){
            fprintf(fFinal, "\n", out_file_path);
            fclose(fFinal);
        }
        else fclose(fFinal);
        printf("Da dich va luu vao file %s\n", file_path);
    }