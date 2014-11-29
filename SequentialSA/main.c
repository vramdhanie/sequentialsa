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

int S;
double T;
int N;

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    
    S = (rand() % 200) + 200 ;
    T = 10;
    N = 100;
    
    int SP;
    int deltaE;
    do{
        printf("Intermediate value: %d\n", S);
        for(int i = 1; i <= N; i++){
            SP = cost();
            deltaE = SP - S;
            if(deltaE < 0 || deltaE < T){
                S = SP;
            }
        }
        T *= 0.95;
    }while(T > 0.1);
    
    printf("Final Value: %d\n", S);
    
    return 0;
}

int cost(){
    int r = rand();
    return r % 1000;
}


