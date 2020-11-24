#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MAXSTRING 100

int main(int argc, char **argv){
//Initislize some variables
    char term[MAXSTRING][MAXSTRING];
    int i;
    FILE *f;
    char line[MAXSTRING];
    char *token;
    char urls[MAXSTRING][MAXSTRING];
    char u[MAXSTRING][MAXSTRING];
    int n[MAXSTRING];
    float p[MAXSTRING];
    
    for (i = 1; i < argc; i++){
        strcpy(term[i-1], argv[i]);
    }
    
    f = fopen("invertedIndex.txt", "r");
    int c = 0;
    while(fgets(line, MAXSTRING, f) != NULL){
        token = strtok(line, " ");
        for (i = 0; i < argc -1; i++){
            if(strcmp(term[i], token) == 0){
                token = strtok(NULL," ");
                while(token != NULL && strcmp(token, "\n") != 0){
                    if (token[strlen(token)-1] == '\n'){
                        token[strlen(token)-1] = '\0';
                    }
                    strcpy(urls[c], token);
                    c++;
                    token = strtok(NULL," ");
                }
                break;
            }
        }
    }
    int j, k = 0;
    /*
    for(j = 0; j < c; j++){
        printf("%s\n", urls[j]);
    }
    printf("\n\n");
    */
    
    for (i = 0; i < c; i++){
        if (urls[i][0] != '\0'){
            strcpy(u[k],urls[i]);
            int count = 1;
            for (j = i+1; j < c; j++){
                if(strcmp(urls[i],urls[j]) == 0){
                    urls[j][0] = '\0';
                    count++;
                }
            }
            n[k] = count;
            k++;
        }
    }

    for (i = 1; i < k; i++){
        int element = n[i];
        strcpy(token, u[i]);
        j = i-1;
        while(j >= 0 && n[j] < element){
            n[j+1] = n[j];
            strcpy(u[j+1],u[j]);
            j--;
        }
        strcpy(u[j+1], token);
        n[j+1] = element;
    }


    for (i = 0;i < k; i++){
        f = fopen("pagerankList.txt", "r");
        while(fgets(line, MAXSTRING, f) != NULL){
            token = strtok(line, ", ");
            if (strcmp(u[i], token) == 0){
                token = strtok(NULL, ", ");
                token = strtok(NULL, ", ");
                if (token[strlen(token)-1] == '\n'){
                    token[strlen(token)-1] = '\0';
                }
                p[i] = atof(token);
            }
        }
        fclose(f);
    }
    
    /*
    for(i = 0; i < k; i++){
        printf("%s, %d, %f\n", u[i], n[i], p[i]);
    }
    printf("\n\n");
    */
    
    int x, y;
    i = 0;
    while(i < k){
        j = i+1;
        while(n[i] == n[j]){
            j++;
        }
        if (i == (j-1)){
            i = j;
            continue;
        }
        
        for (x = i+1; x < j; x++){
            int element = n[x];
            float e = p[x];
            strcpy(token, u[x]);
            y = x-1;
            while(y >= i && p[y] < e){
                p[y+1] = p[y];
                n[y+1] = n[y];
                strcpy(u[y+1],u[y]);
                y--;
            }
            p[y+1] = e;
            strcpy(u[y+1], token);
            n[y+1] = element;
        }
        i = j;
    }
    
    if (k < 30){
        for (i = 0; i < k; i++){
            printf("%s\n", u[i]);
        }
    } else {
        for (i = 0; i< 30; i++){
            printf("%s\n", u[i]);
        }
    }
    
    /*
    for(i = 0; i < k; i++){
        printf("%s, %d, %f\n", u[i], n[i], p[i]);
    }*/
    return 0;
}
