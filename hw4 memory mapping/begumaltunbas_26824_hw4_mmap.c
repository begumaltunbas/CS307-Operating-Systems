//
//  main.c
//  map
//
//  Created by Begum Altunbas on 31.12.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
     
     
int main() {
    
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    int fd= open ("loremipsum.txt",O_RDONLY);
    struct stat s ;
    size_t size;
    int status= fstat(fd, &s);
    size= s.st_size ;
    
    
    char *ptr= mmap(0,size,PROT_READ,MAP_PRIVATE,fd,0);
    int count=0 ;
    if (ptr==MAP_FAILED)
    {
        printf("Mapping failed");
        return 1;
    }
    
    close(fd);
    //ssize_t n= write(1, ptr, size);
    for (int i=0 ; i<size; i++)
    {
        if (ptr[i]=='a')count=count+1;
        
    }
    
    status= munmap(ptr, size);
    if (status !=0)
    {
        printf("Unmapping failed");
        return 1;
    }
    printf("count of char 'a' is %d", count);
    
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(" mmap() took %f seconds to execute \n", cpu_time_used);
    
    return 0;
}
