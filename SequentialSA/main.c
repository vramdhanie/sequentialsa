//
//  main.c
//  SequentialSA
//
//  Created by Vincent Ramdhanie on 11/27/14.
//  Copyright (c) 2014 Vincent Ramdhanie. All rights reserved.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int cost(); //cost function calculates the cost of a certain configuration
void nextConfiguration(); //find another configuration

//define some data structures
int plots[2][2] = {{1,2}, {3,4}};



int main(int argc, const char * argv[]) {
    int S;
    double T;
    int N;
    
    srand(time(NULL));
    
    nextConfiguration();//initialize the array randoly
    S = cost();
    T = 1000;
    N = 1000;
    
    int SP;
    int deltaE;
    do{
        printf("Intermediate value: %d\n", S);
        for(int i = 1; i <= N; i++){
            nextConfiguration();
            SP = cost();
            deltaE = SP - S;
            if(deltaE < 0 || deltaE < T){
                S = SP;
            }
        }
        T *= 0.99;
    }while(T > 0.1);
    
    printf("Final Value: %d\n", S);
    
    return 0;
}

void nextConfiguration(){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            plots[i][j] = (rand() % 1000);
        }
    }
}

int cost(){
    int sum = 0;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                sum += plots[i][j];
            }
        }
    return sum;
}


