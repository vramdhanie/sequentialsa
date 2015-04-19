//
//  generator.h
//  SequentialSA
//
//  Created by Vincent Ramdhanie on 3/15/15.
//  Copyright (c) 2015 Vincent Ramdhanie. All rights reserved.
//

#ifndef __SequentialSA__generator__
#define __SequentialSA__generator__

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#endif /* defined(__SequentialSA__generator__) */

#define PLOT_N 5   /*The size of the plot array*/
#define PLOT_M 5
#define TEMPERATURE 1000 /*Initial temperature*/
#define NUMBER_ITERATIONS 1000 /*Total number of iterations to execute*/

/*
  Performs the generation on the data and stores it in a file
 */
void generate(int a[][PLOT_M]);
void print(int a[][PLOT_M]);

