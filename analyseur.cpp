#include<stdio.h>
#include<stdlib.h>

const char* fileName = "C:\\Users\\yassi\\OneDrive\\Desktop\\Analyseur lexical\\Analyseur-lexicale\\string.lag";
FILE *fileSrc = fopen(fileName, "r");

#include "functions.c"

int main(){
    int k;
    token currentToken = getToken();
    do{
         k = (int) currentToken.name;
         printf("%s ", tokens[k]);
         currentToken = getToken(); 
    }while(currentToken.name != EOF_TOKEN);
    printf("\n\n");
    system("pause");
    return 0;
}
