/*
 This program is aim to calculate the page rank of the pages given by the documents
 
 This program is written by: Yuchen Yan
 
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Graph.h"
#include "math.h"

#define MAXSTRING 1000

void PageRank(float d, float diffPR, int maxIterations){
//--1
//Initialize some variables
    FILE *f;
    Graph g;
    Edge e;
    char line[MAXSTRING];
    char *token;
    
    char t[7][6];               //Store all the urls
    int linkNB[7];              //The number of outlinks of each urls
    float PR[7][maxIterations]; //Store all the pagerank values

    
    
    
    
//--2
//Open the collection file
    if ((f = fopen("collection.txt", "r")) == NULL){
        printf("error!");
        exit(0);
    }
 
    

    
    
//--3
//Get all the urls from the collection file
    int count = 0;              //number of urls in the collection.txt
    while(fgets(line, MAXSTRING, f) != NULL){
        token = strtok(line, " ");
        while(token != NULL && strcmp(token, "\n") != 0){
            if(token[5] == '\n'){
                token[5] = '\0';
            }
            strcpy(t[count],token);
            count++;
            token = strtok(NULL, " ");
        }
    }
   
    
  
    
    
//--4
//Convert the url and all the links into a Graph structure
    g = newGraph(count);
    int i;
    for (i = 0; i< count; i++){
//Get the file name
        char file[10];
        char links[MAXSTRING][MAXSTRING];
        strcpy(file, t[i]);
        strcat(file, ".txt");
//Open each files
        if ((f = fopen(file, "r")) == NULL){
            printf("error!");
            exit(0);
        }
//Get the outlinks from each files
        int c = 0;
        while(fgets(line, MAXSTRING,f) != NULL){
            if (strcmp(line,"#start Section-1\n") == 0){
                continue;
            } else if (strcmp(line,"#end Section-1\n") == 0){
                break;
            }
            token = strtok(line, " ");
            while (token != NULL && strcmp(token,"\n") != 0){
                if(token[5] == '\n'){
                    token[5] = '\0';
                }
                strcpy(links[c], token);
                c++;
                token = strtok(NULL, " ");
            }
        }
//Convert the links into edges and insert edges into the graph
        linkNB[i] = c;
        int j,k;
        for (j = 0; j < c; j++){
            e.v = i;
            for (k = 0; k < count; k++){
                if (strcmp(t[k], links[j]) == 0){
                    e.w = k;
                }
            }
            insertEdge(g, e);

        }
    }
    
 
//--5 initialize the pagerank
    for (i = 0; i < count; i++){
        PR[i][0] = 1.0000000/count;
    }
    
    
    
    
//--6 Calculate the pageranks
    int iteration = 0, j;
    float diff = diffPR;
    while(iteration < maxIterations && diff >= diffPR){
        iteration++;
        for (i = 0; i < count; i++){
            PR[i][iteration] = 0.0;
            for (j = 0; j < count; j++){
                if (g -> edges[j][i] == 1){
                    PR[i][iteration] += PR[j][iteration-1]/linkNB[j];
                }
            }
            PR[i][iteration] = (1.0 - d) / count + d * PR[i][iteration];
        }
        diff = 0.0;
        for (i = 0; i < count; i++){
            diff += fabs(PR[i][iteration]-PR[i][iteration-1]);
        }
    }
    
    for (i = 1; i < count; i++){
        float element = PR[i][iteration];
        int e = linkNB[i];
        char e1[6];
        strcpy(e1, t[i]);
        
        j = i-1;
        while(j >= 0 && PR[j][iteration] < element){
            linkNB[j+1] = linkNB[j];
            strcpy(t[j+1], t[j]);;
            PR[j+1][iteration] = PR[j][iteration];
            j--;
        }
        linkNB[j+1] = e;
        strcpy(t[j+1], e1);
        PR[j+1][iteration] = element;
    }
    
    FILE *f_out;
    f_out = fopen("pagerankList_1.txt", "w");
    for (i = 0; i < 7; i++){
        fprintf(f_out, "%s, %d, %.7f\n",t[i] ,linkNB[i], PR[i][iteration]);
    }

    fclose(f);
    fclose(f_out);
}



int main(int argc, char *argv[]){
    float d;
    float diffPR;
    int maxIterations;
    if (argc == 4){
        d = atof(argv[1]);
        diffPR = atof(argv[2]);
        maxIterations = atoi(argv[3]);
    } else {
        printf("Input error, exiting..");
        exit(0);
    }
    PageRank(d, diffPR, maxIterations);
    
    return 0;
}
