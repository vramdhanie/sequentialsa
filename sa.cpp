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
#include "generator.h"
#include "generator.cpp"
#include <string>
#include <vector>

using namespace std;

long double cost(); //cost function calculates the cost of a certain configuration
void nextConfiguration(); //find another configuration
void loadData(); //load all data from the input file
void printVector();

//define some data structures
vector< vector<long double> > plots;
vector< vector<long double> > landUses;
vector< pair<int, int> > assignments;

int main(int argc, const char * argv[]) {

    int S;
    double T;
    int N;

    srand(time(NULL));

    //nextConfiguration();//initialize the array randomly
    //S = cost();
    T = TEMPERATURE;
    N = NUMBER_ITERATIONS;
/*
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
*/
    loadData();
    cout << "Plots: " << plots.size() << "\tLand Uses: " << landUses.size() << "\tAssigments: " << assignments.size() << endl;
    //printVector();
    cout << "Cost of current config: " << cost() << "\n";
    nextConfiguration();
    cout << "Cost of next config: " << cost() << "\n";
    return 0;
}

/*
   Change the assignment of uses to plots in a random
   way.
*/
void nextConfiguration(){
  int p = rand() % plots.size();
  int us = assignments[p].second;

  int q = rand() % plots.size();
  int us2 = assignments[q].second;
  while(us == us2 ){
    q = rand() % plots.size();
    us2 = assignments[q].second;
  }

  assignments[p].second = assignments[q].second;
  assignments[q].second = us;

}

/*
   Calculate the cost of the current configuration
*/
long double cost(){
    long double sum = 0;
    for (vector< pair<int, int> >::iterator it = assignments.begin() ; it != assignments.end(); ++it){
      vector< long double > plot = plots[it->first];
      vector< long double > landUse = landUses[it->second];
      for(int i = 0; i < plot.size(); i++){
        sum += plot[i] * landUse[i];
      }
    }
    cout << '\n';
    return sum;
}

/*
    Load the data from the text file.
*/
void loadData(){
    std::fstream myfile("../DataGenerator/data_1.txt", std::ios_base::in);

    int n, m, l, p, a;

    //find total number of plots n and number of attributes m
    myfile >> n >> m;

    //printf("%d\t%d\n", n, m);


    float b;
     //find all attributes for all plots
    int num_plots = n * m;
    int count = 0;
    for (int i = 0; i < n; i++){
      vector<long double> row;
      long double r;
      for (int j = 0; j < m; j++){
        myfile >> r;
        row.push_back(r);
        count++;
      }
      plots.push_back(row);
    }

    cout << "Total rows read: " << plots.size() << endl;

    printf("Number of values read: %d of %d\n", count, num_plots);

    //find total number of land uses and criteria then load all values
    myfile >> l >> m;
    int num_landUses = l * m;
    count = 0;
    for(int i = 0; i < l; i++){
      vector<long double> row;
      long double r;
      for (int j = 0; j < m; j++ ){
        myfile >> r;
        row.push_back(r);
        count++;
      }
      landUses.push_back(row);
    }
    printf("Number of values read: %d of %d\n", count, num_landUses);

    //find all assignments
    for(int i = 0; i < n; i++){
      myfile >> p >> a;
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
