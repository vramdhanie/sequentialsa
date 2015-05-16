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
    
    ofstream outStream;
    outStream.open("plots");
    if(outStream.fail()){
        cout << "Failed to open output file\n";
        exit(1);
    }

    for(int i = 0; i < PLOT_N; i++){
        for(int j = 0; j < PLOT_M; j++){
            outStream << a[i][j] << " ";
        }
        outStream << std::endl;
    }


    outStream.close();
}
