#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mahoa.h" 
#define Alphabet_len 33

void dichkitu(char *word, char *str, int n){
        if(word[0]=='m'||word[0]=='M'){
        int e=0;
        int o=0;
        int w=0;
        int i=1;
        while(word[i]=='e'){e++; i++;}
        while(word[i]=='o'){o++; i++;}
        while(word[i]=='w'){w++; i++;}
        int index= (e-1)*9+(o-1)*3+(w-1);
        if(n==1){
            if(index>=0 && index<Alphabet_len){
                if(word[0]=='M') printf("%c", 'A'+index);
                else printf("%c", ALPHABET[index]);
            }
            else{
                printf("%c", ALPHABET[32]);
            }
        }
        else{
            FILE *fWrite = fopen(str, "a");
            if (fWrite == NULL) {
                printf("Khong the mo file de ghi.\n");
                return;
            }
            if(index>=0 && index<Alphabet_len){
                if(word[0]=='M') fprintf(fWrite,"%c", 'A'+index);
                else fprintf(fWrite,"%c", ALPHABET[index]);
            }
            else{
                fprintf(fWrite,"%c", ALPHABET[32]);
            }
            fclose(fWrite);
        }
    }
}
void dichso(char *word, char *str, int n){
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
                if(n==1) printf("-");
                else{
                    FILE *fWrite=fopen(str, "a");
                    if(fWrite!=NULL){
                        fprintf(fWrite, "-");
                        fclose(fWrite);
                    }
                }
            }
            int so_thuc = (so[0] == 'M' && so_dau == 0 && da_in_dau_cham == 0) ? 1 : 0;
            int e=0;
            int o=0;
            int w=0;
            int i=1;
            while(so[i]=='e'){e++; i++;}
            while(so[i]=='o'){o++; i++;}
            while(so[i]=='w'){w++; i++;}
            int index= (e-1)*9+(o-1)*3+(w-1)-33;
            if(n==1){
                if(so_thuc){
                    printf(".");
                    da_in_dau_cham=1;
                }
                printf("%d", index);
            }
            else{
                FILE *fWrite = fopen(str, "a");
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
        }
        so_dau=0;
    }
}
void dichphu(char *source, char *str, int n){
    char *p=source;
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
            dichso(word, str, n);
        }
        else{
            dichkitu(word, str, n);
        }
    }
}
void dich(char *str,int n){
    if(n==1){
        dichphu(str, str, 1);
        printf("\nDa dich.\n");
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
        dichphu(content, str, 2);
        FILE *fFinal=fopen(str, "a");
        if(fFinal!=NULL){
            fprintf(fFinal, "\n", str);
            fclose(fFinal);
        }
        else fclose(fFinal);
        printf("Da dich va luu vao file %s\n", str);
    }
}
