#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <getopt.h>

#include "cpufreq.h"
#include "cpupower_intern.h"

#include "cpufreq.h"
#include "sysfs.h"
#include "helpers.h"
#include "bitmask.h"
#define LINE_LEN 10

#include <time.h>  

void times()
{
time_t t = time(NULL);
struct tm tm = *localtime(&t);
printf(" %d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

 unsigned int count_cpus(void);
 void get_freq_stats(unsigned int cpu, unsigned int human, char (*arr)[][1000]);
 void print_speed(unsigned long speed);
 int count_freq_stats(unsigned int cpu, unsigned int human);
 void timestamp();


int main()
{ 
 int s = count_freq_stats(0,1);
 int c = count_cpus();
 char arr[c][1000][1000];
 
 while(1)
{ 
   for(int i=0;i<c;i++)
   { 
     get_freq_stats(i,1, arr[i]);
     
   }
  
  
   for (int i = 0; i < s; ++i) 
   {
     times();
     for (int j = 0; j < c; ++j)
     {			
      printf("%10s%%", arr[j][i]);
     }
     printf("\n");
   }
   
   sleep(1);
   printf("\n");
}

 return 0;
 }





