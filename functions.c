#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define IDFSIZE 50 
#define NUMBERSIZE 32 
#define VARCHARSIZE 225 

#include "functions.h"

int keyword_token_size = sizeof(keyword_token)/sizeof(keyword_token[0]);
int symbole_token_size = sizeof(symbole_token)/sizeof(symbole_token[0]);

boolean isNumber = FALSE;

boolean isAlphabetic(char c);
boolean isNumeric(char c);
int caractereSpecial(char c);
numberToken getNumber(char digit, boolean isNegative);
token getToken();

boolean isAlphabetic(char c){
     if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'){
        return TRUE;
     }
     return FALSE;
}

boolean isNumeric(char c){
     if(c >= '0' && c <= '9'){
         return TRUE;
     }
     return FALSE;
}

int caractereSpecial(char c){
    int i = 0;
    int symbole = (int) STAR_TOKEN;
    while(i < symbole_token_size){
          if(c == symbole_token[i]){
               symbole = symbole + i;
               return symbole;
          }
          i++;
    }
    return -1;
}

numberToken getNumber(char digit, boolean isNegative){
     int i=0;
     boolean isInt = TRUE;
     char* memory = (char *)malloc(NUMBERSIZE*sizeof(char));
     numberToken A;
     do{
         memory[i] = digit;
         digit = fgetc(fileSrc); 
         i++;
         if(digit == '.'){ 
              isInt = FALSE;
              memory[i] = '.';
              digit = fgetc(fileSrc); 
              i++;
         }
     }while(isNumeric(digit) == TRUE);
     memory[i] = '\0';

     ungetc(digit, fileSrc);
     A.isInt = isInt;
     if(isInt == TRUE){ 
          A.value.n = atoi(memory);
          if(isNegative == TRUE){
               A.value.n = - A.value.n;
          }
     }else{ 
          A.value.x = atof(memory);
          if(isNegative == TRUE){
               A.value.x = - A.value.x;
          }
     }
     return A;
}

token getToken(){
     char character = fgetc(fileSrc);
     token A;
     int i = 0;
     boolean previousIsNumer = isNumber;
     isNumber = FALSE;
     
     if(character == ' ' || character == '\t' || character == '\n'){
          return getToken();
     }
     
     else if(isAlphabetic(character) == TRUE){
          
          A.properties.idf.name = (char *)malloc(IDFSIZE*sizeof(char));
          
          do{
          A.properties.idf.name[i] = character;
          character = fgetc(fileSrc); 
          i++;
          }while(isAlphabetic(character) == TRUE || isNumeric(character) == TRUE);
          A.properties.idf.name[i] = '\0'; 
          
          ungetc(character, fileSrc);
          i = 0;
          
          while(i < keyword_token_size){
               if(strcmp(A.properties.idf.name, keyword_token[i]) == 0){ 
               A.name = (nameToken) i;
               free(A.properties.idf.name);
               return A; 
               }
               i++;
          }
          A.name = IDF_TOKEN;
          return A; 
     }
     
     else if(isNumeric(character) == TRUE){
     isNumber = TRUE;
     A.name = NUMBER_TOKEN;
     
     A.properties.number = getNumber(character, FALSE);
     return A;
     }
     else if(character == '+' || character == '-'){
          nameToken symboleToken = (character == '+' ? PLUS_TOKEN : MINUS_TOKEN);
          boolean isNegative = (character == '-' ? TRUE : FALSE);
          
          do{
               character = fgetc(fileSrc);
          }while(character == ' ');
          
          if(isNumeric(character) == TRUE){
               
               if(previousIsNumer == TRUE){
                    ungetc(character, fileSrc);
                    A.name = symboleToken;
                    return A;
               }else{ 
                    isNumber = TRUE;
                    A.name = NUMBER_TOKEN;
                    A.properties.number = getNumber(character, isNegative);
                    return A;
               }
          }else{ 
               ungetc(character, fileSrc);
               A.name = symboleToken;
               return A;
          }
     }
     
     else if(character == '"' || character == '\''){
          i = 0;
          char d = character;
          
          char previousC = ' ';

          character = fgetc(fileSrc);
          
          A.properties.varchar.value = (char *)malloc(VARCHARSIZE*sizeof(char));
          
          while((character != d || (character == d && previousC == '\\')) && character != EOF){
          A.properties.varchar.value[i] = character;
          character = fgetc(fileSrc);
          i++;
          previousC = A.properties.varchar.value[i-1];
          }
          A.properties.varchar.value[i] = '\0';
          A.name = VARCHAR_TOKEN;
          A.properties.varchar.c = d;
          return A;
     }
     
     else if(character == '/'){
          character = fgetc(fileSrc);
          if(character == '/'){ 
          
          do{
               character = fgetc(fileSrc);
          }while(character != '\n' && character != EOF);
          return getToken(); 
          }
          else if(character == '*'){ 
          do{
               character = fgetc(fileSrc);
          }while(character != '*');
          
          character = fgetc(fileSrc);
          if(character == '/'){ 
                    return getToken(); 
               }
          }
          else{
               A.name = DIV_TOKEN;
               ungetc(character, fileSrc);
               return A;
          }
     }
     else if((i = caractereSpecial(character)) > -1){
          A.name = (nameToken) i;
          return A;
     }
     else if(character == '='){
          character = fgetc(fileSrc);
          if(character == '='){
               A.name = OP_EQ_TOKEN;
               return A;
          }else{ 
               A.name = ASSIGNMENT_TOKEN;
               ungetc(character, fileSrc);
               return A;
          }
     }
     else if(character == '>'){
          character = fgetc(fileSrc);
          if(character == '='){ 
               A.name = OP_GE_TOKEN;
               return A;
          }else{ 
               A.name = GT_TOKEN;
               ungetc(character, fileSrc);
               return A;
          }
     }
     else if(character == '<'){
          character = fgetc(fileSrc);
          if(character == '='){ 
               A.name = OP_LE_TOKEN;
               return A;
          }else{ 
               A.name = LT_TOKEN;
               ungetc(character, fileSrc);
               return A;
          }
     }
     else if(character == EOF){
          A.name = EOF_TOKEN;
          return A;
     }else{
          A.name = ERROR_TOKEN;
          return A;
     }
}
