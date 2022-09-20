#include "stdlib.h"
#include "stdio.h"


int isLetter(char ch){
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? 1 : 0;
}

int main(char*args[],char *argv[]){

    printf("%d",isLetter('A'));
    printf("%d",isLetter('$'));
    printf("%c","\\'");
    return 0;
}