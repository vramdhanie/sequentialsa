//
//  main.c
//  SequentialSA
//
//  Created by Vincent Ramdhanie on 11/27/14.
//  Copyright (c) 2014 Vincent Ramdhanie. All rights reserved.
//

#include <time.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include "sa.h"
#include <string>
#include <vector>

using namespace std;

long double cost(vector< pair<int, int> >&); //cost function calculates the cost of a certain configuration
pair<int, int> nextConfiguration(vector< pair<int, int> >&); //find another configuration
void loadData(std::fstream&); //load all data from the input file
void printVector(); //print the  content of the plots vector
void revert(pair<int, int>, vector< pair<int, int> >&); //revert a configuration change
void sa(int, int, vector< pair<int, int> >&); //perform the sequential SA algorithm
void experiment(); //manage the experiment

//define some data structures
vector< vector<long double> > plots;
vector< vector<long double> > landUses;
vector< pair<int, int> > assignments;

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    experiment();
    return 0;
}

/*
   Manage the process of loading data, running the experiment
   and saving the results.
*/
void experiment(){
  for(int k = 0; k < NUMBER_OF_INPUT_FILES; k++){
    std::fstream myfile(BASE_FILE_PATH + BASE_FILE_NAME + std::to_string(k) + FILE_EXT, std::ios_base::in);
    loadData(myfile);
    myfile.close();
    cout << "Plots: " << plots.size() << "\tLand Uses: " << landUses.size() << "\tAssigments: " << assignments.size() << endl;
    vector< pair<int, int> > a;
    for(int i = 1; i <= ITERATIONS_PER_FILE; i++){
      a = assignments;
      sa(k, i, a);
    }
}
}

/*
   Perform Sequential Simulated Annealing Algorithm
*/
void sa(int fileNum, int iterNum, vector< pair<int, int> > &a){
  long double T;
  int N;
  T = TEMPERATURE;
  N = NUMBER_ITERATIONS;
  long double S;
  long double SP;
  long double deltaE;

  S = cost(a);
  pair<int, int> change;

  ofstream out ("result_" + std::to_string(fileNum) + "_"+ std::to_string(iterNum) + FILE_EXT);

  do{
      out << T << ", " << S << "\n";
      for(int i = 1; i <= N; i++){
          change = nextConfiguration(a);
          SP = cost(a);
          deltaE = SP - S;
          if(deltaE < 0 || deltaE < T){
              S = SP;
          }else{
            revert(change, a);
          }
          out << T << ", " << S << "\n";
      }
      T *= TEMPERATURE_DECREMENT;
  }while(T > TEMPERATURE_FINAL);
  cout << "Final Value: " << S << "\n";
  out.close();
}

/*
   Change the assignment of uses to plots in a random
   way.
*/
pair<int, int> nextConfiguration(vector< pair<int, int> > &a){
  int p = rand() % plots.size();
  int us = a[p].second;

  int q = rand() % plots.size();
  int us2 = a[q].second;
  while(us == us2 ){
    q = rand() % plots.size();
    us2 = a[q].second;
  }

  a[p].second = a[q].second;
  a[q].second = us;

  return make_pair(p, q);
}

void revert(pair<int, int> swap, vector< pair<int, int> > &a){
  int temp = a[swap.first].second;
  a[swap.first].second = a[swap.second].second;
  a[swap.second].second = temp;
}

/*
   Calculate the cost of the current configuration
*/
long double cost(vector< pair<int, int> > &a){
    long double sum = 0;
    for (vector< pair<int, int> >::iterator it = a.begin() ; it != a.end(); ++it){
      vector< long double > plot = plots[it->first];
      vector< long double > landUse = landUses[it->second];
      for(int i = 0; i < plot.size(); i++){
        sum += plot[i] * landUse[i];
      }
    }
    return sum;
}

/*
    Load the data from the text file.
*/
void loadData(std::fstream& dataFile){

    int n, m, l, p, a;

    //find total number of plots n and number of attributes m
    dataFile >> n >> m;

    float b;
     //find all attributes for all plots
    int num_plots = n * m;
    int count = 0;
    for (int i = 0; i < n; i++){
      vector<long double> row;
      long double r;
      for (int j = 0; j < m; j++){
        dataFile >> r;
        row.push_back(r);
        count++;
      }
      plots.push_back(row);
    }

    //find total number of land uses and criteria then load all values
    dataFile >> l >> m;
    int num_landUses = l * m;
    count = 0;
    for(int i = 0; i < l; i++){
      vector<long double> row;
      long double r;
      for (int j = 0; j < m; j++ ){
        dataFile >> r;
        row.push_back(r);
        count++;
      }
      landUses.push_back(row);
    }

    //find all assignments
    for(int i = 0; i < n; i++){
      dataFile >> p >> a;
      assignments.push_back(make_pair(p, a));
    }

}

void printVector(){

  for (vector<vector<long double> >::size_type i = 0; i < plots.size(); i++){
    for (vector<long double>::size_type j = 0; j < plots[i].size(); j++){
      cout << plots[i][j] << " ";
    }
    cout << endl;
  }

}



/**
#include <sstream>
#include <string>

for(std::string line; std::getline(source, line); )   //read stream line by line
{
    std::istringstream in(line);      //make a stream for the line itself

    std::string type;
    in >> type;                  //and read the first whitespace-separated token

    if(type == "triangle")       //and check its value
    {
        float x, y, z;
        in >> x >> y >> z;       //now read the whitespace-separated floats
    }
    else if(...)
        ...
    else
        ...
}


AND A SECOND OPTION:
#include <string>
#include <deque>
#include <vector>
#include "strtk.hpp"
int main()
{
   std::string int_string = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15";
   std::vector<int> int_list;
   strtk::parse(int_string,",",int_list);

   std::string double_string = "123.456|789.012|345.678|901.234|567.890";
   std::deque<double> double_list;
   strtk::parse(double_string,"|",double_list);

   return 0;
}
*/
