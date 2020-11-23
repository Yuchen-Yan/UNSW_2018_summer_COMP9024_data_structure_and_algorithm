#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "DLListStr.h"
#include "InvertedIdx.h"

#define MAXSTRING 1000

char *strlwr(char *s)
{
    char *str;
    str = s;
    while(*str != '\0')
    {
        if(*str >= 'A' && *str <= 'Z') {
            *str += 'a'-'A';
        }
        str++;
    }
    return s;
}



int main(int argc, char **argv){
    FILE *f;
    char line[MAXSTRING];
    char *token;
    char url[MAXSTRING][6];
    
    f = fopen("collection.txt", "r");
    int c = 0;
    while(fgets(line, MAXSTRING, f) != NULL){
        token = strtok(line, " ");
        while(token != NULL && strcmp(token,"\n") != 0){
            if(token[5] == '\n'){
                token[5] = '\0';
            }
            strcpy(url[c], token);
            c++;
            token = strtok(NULL," ");
        }
    }
    
    
    int i;
    char *file;
    FILE *f1;
    Tree t = newTree();
    for(i = 0 ; i < c; i++){
        strcpy(file,url[i]);
        strcat(file, ".txt");
        f1 = fopen(file, "r");
        
        while(fgets(line, MAXSTRING, f1) != NULL){
            if(strcmp(line,"#start Section-2\n") == 0){
                break;
            }
        }
        while(fgets(line, MAXSTRING, f1) != NULL){
            if (strcmp(line, "#end Section-2\n") == 0){
                break;
            }
            token = strtok(line," ");
            while(token != NULL && strcmp(token, "\n") != 0){
                if (token[strlen(token) - 1] == '\n'){
                    token[strlen(token) -1] = '\0';
                }
                if(token[strlen(token) - 1] == '.' || token[strlen(token) - 1] == ',' || token[strlen(token) - 1] == ';' || token[strlen(token) - 1] == '?'){
                    token[strlen(token) -1] = '\0';
                }
                token = strlwr(token);
                //printf("%s\n", token);
                t = TreeInsert(t, token, url[i]);
                token = strtok(NULL, " ");
            }
        }
        
    }
    FILE *f2 = fopen("invertedIndex.txt","w");
    showTree(f2,t);
    fclose(f);
    fclose(f1);
    fclose(f2);

    
    
    
    
    return 0;
}







