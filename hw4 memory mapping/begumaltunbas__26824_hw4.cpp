//
//  main.cpp
//  begumaltunbas_hw4
//
//  Created by Begum Altunbas on 28.12.2020.
//
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <chrono>
using namespace std::chrono;
  

using namespace std;

int main() {
    
    auto start = high_resolution_clock::now();

    string line;
    ifstream file("loremipsum.txt") ;
    
    int count=0 ;
    
    while (getline(file, line))
    {
        istringstream iss1 (line);
        
        char ch;
        
        while ( iss1>> ch)
        {
            if (ch=='a') count++;
        }
        
    }
    
   
    cout<<"count of char 'a' is "<< count<<endl  ;
    auto stop = high_resolution_clock::now();
   // file.close();
    
    auto duration = duration_cast<seconds>(stop - start);
    cout<< "getline,istringstream() took "<< duration.count() <<  " seconds to execute " <<  endl;
    
    
    return 0;
}
