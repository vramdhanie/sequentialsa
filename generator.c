//
//  generator.c
//  SequentialSA
//
//  Created by Vincent Ramdhanie on 3/15/15.
//  Copyright (c) 2015 Vincent Ramdhanie. All rights reserved.
//

#include "generator.h"

void generate(int a[][PLOT_M]){
    
    
    for(int i = 0; i < PLOT_N; i++){
        for(int j = 0; j < PLOT_M; j++){
            a[i][j] = (rand() % 1000);
        }
    }

    
}

void print(int a[][PLOT_M]){
    FILE *fp;
    fp = fopen("plots", "w+");
    fprintf(fp, "%d", 100);
    
    for(int i = 0; i < PLOT_N; i++){
        for(int j = 0; j < PLOT_M; j++){
            fprintf(fp, "%d ", a[i][j]);
        }
        fprintf(fp,"\n");
    }
    
    fclose(fp);
}