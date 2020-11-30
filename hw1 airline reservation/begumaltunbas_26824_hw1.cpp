//
//  main.cpp
//  begumaltunbas_26824_hw1
//
//  Created by Begum Altunbas on 6.11.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <vector>
#include <random>
#include <stdlib.h> // for srand(time)
#include <time.h>   // for srand(time)

using namespace std;



//created cell struct to use in matrix
struct cells
{
    int thread_id;
    int seat_number;
    int count;
};

int rem_seat_num=100;
int turn =0 ;
int full_count=0 ;
vector<vector<cells> > matrix(2,vector<cells>(50));


void assign_seat_numbers()
{
    for (int i = 0 ;i <matrix.size(); i++)
    {
        for (int j=0 ; j<matrix[0].size();j++)
        {
            if (i==0)
            {
                matrix[i][j].seat_number=j+1;
            }
            else
            {
                matrix[i][j].seat_number=j+51;
            }
        }
    }
}

void print_matrix (vector<vector<cells> > &matrix)
{
    for (int i = 0 ;i <matrix.size(); i++)
    {
        for (int j=0 ; j<matrix[0].size();j++)
        {
            cout<< matrix[i][j].thread_id<< " ";
            //cout<< matrix[i][j].seat_number<<" ";
        }
        cout<< endl ;
    }
    
}




//functions for seat assigning for each seperate thread
void * func_id1 (void *data)
{
   // bool flag=true;
    while (rem_seat_num!=0)
    {
        int seat = rand() % 100 + 1; //generate rand num 1-100
    
        while (turn!=0){} //busy waiting loop so that while other thread is working this one waits in the critical region
        cout<< "Agency 1 Entered Critical Region"<<endl ;
        if (seat>50 &&  matrix [1][seat-51].thread_id==0 && rem_seat_num!=0) //assgining seats if renadom generated one is avaliable
        {
            //cout<< "Agency 1 Entered Critical Region"<<endl ;
            matrix [1][seat-51].thread_id=1;
            cout<< "Seat Number "<< seat << " is reserved by Agency 1"<<endl ;
            matrix[0][seat-51].count++;
            rem_seat_num--;
            if (rem_seat_num==0)
            {
               // cout<< "No Seats Left"<<endl ;
                cout<< "Agency 1 Exit Critical Region"<< endl ;
                cout<<endl ;
                turn=1 ;
                break ;

            }
            //cout<< "Agency 1 Exit Critical Region"<< endl ;
            
        }
        else if (seat<=50 && matrix[0][seat-1].thread_id==0 && rem_seat_num!=0 )
        {
            //cout<< "Agency 1 Entered Critical Region"<<endl ;
            matrix[0][seat-1].thread_id=1;
            cout<< "Seat Number "<< seat << " is reserved by Agency 1"<<endl ;
            matrix[0][seat-1].count++;
            rem_seat_num--;
            if (rem_seat_num==0)
            {
                //cout<< "No Seats Left"<<endl ;
                cout<< "Agency 1 Exit Critical Region"<< endl ;
                cout<<endl ;
                turn=1 ;
                break ;

            }
            //cout<< "Agency 1 Exit Critical Region"<< endl ;
           // cout<< endl ;
        }
            
        // cout<< "Agency 1 Exit Critical Region"<< endl ;
        if (rem_seat_num==0)
        {
            full_count++;
            if (full_count==1)
            {
                //cout<< "Agency 1 Entered Critical Region"<<endl ;
                cout<< "Agency 1 Exit Critical Region"<< endl ;
                cout<< "No Seats Left"<<endl ;
                cout<< endl ;
                turn=1;
                break ;
            }

        }
        cout<< "Agency 1 Exit Critical Region"<< endl ;
        cout<<endl ;
        turn=1;
        
    }
    return NULL ;
}



void * func_id2 (void * data)
{
   
    while (rem_seat_num!=0)
    {
        int seat = rand() % 100 + 1; //generate rand num 1-100
        
        while (turn!=1){} //busy waiting loop so that while other thread is working this one waits in the critical region
       
         cout<< "Agency 2 Entered Critical Region"<<endl ;
        
            if (seat>50 &&  matrix [1][seat-51].thread_id==0 && rem_seat_num!=0 ) //assgining seats if renadom generated one is avaliable
                   {
                        //cout<< "Agency 2 Entered Critical Region"<<endl ;
                       matrix [1][seat-51].thread_id=2;
                       cout<< "Seat Number "<< seat << " is reserved by Agency 2"<<endl ;
                       matrix[0][seat-51].count++;
                       rem_seat_num--;
                      // cout<< "Agency 2 Exit Critical Region"<< endl ;
                      // cout<< endl ;
                       if (rem_seat_num==0)
                       {
                          // cout<< "No Seats Left"<<endl ;
                            cout<< "Agency 2 Exit Critical Region"<< endl ;
                           cout<<endl ;
                            turn=0 ;
                            break ;

                       }
                   }
            else if (seat<=50 && matrix[0][seat-1].thread_id==0  && rem_seat_num!=0)
            {
                // cout<< "Agency 2 Entered Critical Region"<<endl ;
                matrix[0][seat-1].thread_id=2;
                cout<< "Seat Number "<< seat << " is reserved by Agency 2"<<endl ;
                matrix[0][seat-1].count++;
                rem_seat_num--;
                if (rem_seat_num==0)
                {
                    //cout<< "No Seats Left"<<endl ;
                    cout<< "Agency 2 Exit Critical Region"<< endl ;
                    cout<<endl ;
                    turn=0 ;
                    break ;
                }
               // cout<< "Agency 2 Exit Critical Region"<< endl ;
                //cout<< endl ;
            }
             
        if (rem_seat_num==0) //when there are no seats left
        {
            full_count++;
            if (full_count==1)
            {
               // cout<< "Agency 1 Entered Critical Region"<<endl ;
                cout<< "Agency 2 Exit Critical Region"<< endl ;
                cout<< "No Seats Left"<<endl ;
                cout<< endl ;
                turn=0;
                break;

            }
        }
        cout<< "Agency 2 Exit Critical Region"<< endl ;
        cout<<endl ;
        turn=0 ;
    }
    
    return NULL;
}




int main() {
    srand (time(NULL));
    pthread_t thread1;
    pthread_t thread2;
    
 
    pthread_create( &thread1, NULL, &func_id1, NULL);
    pthread_create( &thread2, NULL, &func_id2, NULL);
    
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL); //joining threads here so that main waits for them to finish first
 
    if (rem_seat_num==0) //when the plane is full print seating plan with thread ids
       {
           cout<<"Plane is full:"<<endl ;
           print_matrix(matrix);
       }

    return 0;
}

