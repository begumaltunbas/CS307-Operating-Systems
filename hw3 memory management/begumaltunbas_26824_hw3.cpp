#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h> 
#include <queue>
#include <semaphore.h>
using namespace std;

#define NUM_THREADS 10
#define MEMORY_SIZE 150

struct node
{
	int id;
	int size;
};



queue<node> myqueue; // shared que
pthread_mutex_t sharedLock = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_t server; // server thread handle
sem_t semlist[NUM_THREADS]; // thread semaphores

int thread_message[NUM_THREADS]; // thread memory information
char  memory[MEMORY_SIZE]; // memory size





int start=0 ;
//int start_index=0 ;

void my_malloc(int thread_id, int size)
{
	//This function will add the struct to the queue
    node  my_thread;
    my_thread.id=thread_id;
    my_thread.size=size;
    myqueue.push(my_thread);
}

void * server_function(void *)
{
	//This function should grant or decline a thread depending on memory size.
  
  //  int start_index=0 ;
    while (true)
    {
        
        if (myqueue.empty()==false)
        {
            //pthread_mutex_lock(&sharedLock);
            node in_line= myqueue.front();
            myqueue.pop();
         
            if (in_line.size < MEMORY_SIZE-start)
            {
                //thread_message[in_line.id]=start_index ;
                thread_message[in_line.id]=start;
               // start_index=start_index+in_line.size;
            }
            else
            {
                thread_message[in_line.id]=-1 ;
               
            }
            
            sem_post(&semlist[in_line.id]) ;
           //pthread_mutex_unlock(&sharedLock);
        }
      //  if (counter==10) break;
        
        
    }
   
    
    return NULL;
}

void * thread_function(void * id) 
{
	//This function will create a random size, and call my_malloc
   
    pthread_mutex_lock(&sharedLock);
    int * temp= (int*) id;
       
    int random=((rand() % MEMORY_SIZE/6)+1) ;
    
   
    my_malloc(*temp, random);
   
    //Block
    sem_wait(&semlist[*temp]);
    
	//Then fill the memory with id's or give an error prompt
    if (thread_message[*temp]==-1)
    {
        cout<<"Thread ID: "<<*temp<<" Not enough memory"<<endl ;
    }
    else
    {
        char ch= '0'+ *temp;
        for (int i=start; i<start+random; i++)
        {
            memory [i]=ch;
        }
        start=start+random;
    }
    
     pthread_mutex_unlock(&sharedLock);

    return NULL;
}


void init()	 
{
	pthread_mutex_lock(&sharedLock);	//lock
	for(int i = 0; i < NUM_THREADS; i++) //initialize semaphores
	{sem_init(&semlist[i],0,0);}
	for (int i = 0; i < MEMORY_SIZE; i++)	//initialize memory 
  	{char zero = '0'; memory[i] = zero;}
   	pthread_create(&server,NULL,server_function,NULL); //start server 
	pthread_mutex_unlock(&sharedLock); //unlock
}



void dump_memory() 
{
 // You need to print the whole memory array here.
    cout<< "Memory Dump: " ;
    
    for (int i = 0 ;i< MEMORY_SIZE;i++)
    {
        cout<< memory[i] ;
    }
    
}

int main (int argc, char *argv[])
 {

 	//You need to create a thread ID array here
     pthread_t threadlist [NUM_THREADS];
     int threadnums[NUM_THREADS];
    
     for (int i=0; i<NUM_THREADS; i++)
     {
        threadnums[i]=i ;
     }

 	init();	// call init
    
 	//You need to create threads with using thread ID array, using pthread_create()
     for (int j=0;j< NUM_THREADS; j++)
     {
         pthread_create( &threadlist[j], NULL,thread_function, (void* )&threadnums[j]); //buraya parametreleri yaz
     }
     

     
 	//You need to join the threads
     for (int x=0 ;x < NUM_THREADS; x++)
     {
         pthread_join(threadlist[x], NULL);
     }
     
 	dump_memory(); // this will print out the memory
 	
     
 
    printf("\nMemory Indexes:\n" );
 	for (int i = 0; i < NUM_THREADS; i++)
 	{
 		printf("[%d]" ,thread_message[i]); // this will print out the memory indexes
 	}
 	printf("\nTerminating...\n");
    
    
 }
