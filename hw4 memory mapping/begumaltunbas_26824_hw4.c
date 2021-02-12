//
//  main.c
//  begumaltunbas_hw4c
//
//  Created by Begum Altunbas on 28.12.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    
    clock_t start, end;
    double cpu_time_used;
    
    int count=0 ;
    start = clock();
    char file_name[35] ="loremipsum.txt" ;
   // char buffer [30];
    FILE * fp ;
    char ch;
    
    
    fp= fopen(file_name,"r"); // read only
    
    while ((ch=getc(fp))!= EOF)
    {
        if (ch=='a') ++count;
        
    }
       
    
    printf("count of char 'a' is %d", count);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(" fopen() took %f seconds to execute \n", cpu_time_used);
    return 0;
}
