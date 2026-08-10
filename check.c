#include "mahoa.h"

int checkso(char *input_str, int i){
    if(input_str[i]>='0' && input_str[i]<='9'){
        return 1;
    }
    else if((i>0 && input_str[i-1]=='-') && input_str[i]>='0' && input_str[i]<='9'){
        return 1;
    }
    else if(input_str[i]=='.' && input_str[i+1]>='0' && input_str[i+1]<='9' && input_str[i-1]>='0' && input_str[i-1]<='9' && i>0){
        return 1;
    }
    return 0;
}