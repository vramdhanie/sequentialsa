#ifndef FINAL_SEQUENTIALSA_SA_H_
#define FINAL_SEQUENTIALSA_SA_H_

#define TEMPERATURE 100 /*Initial temperature*/
#define TEMPERATURE_DECREMENT 0.99 /*The amount by which teh temperature is decrement each iteration*/
#define TEMPERATURE_FINAL 0.01 /*The coolest temperature, time to stop*/
#define NUMBER_ITERATIONS 100 /*Total number of iterations to execute before reducing temperature*/
#define ITERATIONS_PER_FILE 10 /*Number of times to run each input file*/
#define BASE_FILE_PATH "../DataGenerator/" /*Where input files are located*/
#define BASE_FILE_NAME "data_" /*Name of data files*/
#define FILE_EXT ".txt" /*file extension to use*/
#define NUMBER_OF_INPUT_FILES 10 /*How many data files*/


#endif  // FINAL_SEQUENTIALSA_SA_H_
