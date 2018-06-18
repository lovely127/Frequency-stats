#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include <getopt.h>

#include "cpufreq.h"
#include "sysfs.h"
#include "helpers.h"
#include "bitmask.h"
#define LINE_LEN 10

int count_freq_stats(unsigned int cpu, unsigned int human);
static int no_rounding;
void print_speed(unsigned long speed)
{
	unsigned long tmp;

	if (no_rounding) 
       {
		if (speed > 1000000)
			printf("%u.%06u GHz", ((unsigned int) speed/1000000),((unsigned int) speed%1000000));

		else if (speed > 1000)
			printf("%u.%03u MHz", ((unsigned int) speed/1000),(unsigned int) (speed%1000));

		else
			printf("%lu kHz", speed);
      } 
      else 
      {
		if (speed > 1000000)
                {
			tmp = speed%10000;
			if (tmp >= 5000)
			speed += 10000;
			printf("%u.%02u GHz", ((unsigned int) speed/1000000),((unsigned int) (speed%1000000)/10000));
		} 
              else if (speed > 100000)
               {
			tmp = speed%1000;
			if (tmp >= 500)
			speed += 1000;
			printf("%u MHz", ((unsigned int) speed/1000));
	       }
            else if (speed > 1000) 
              {
			tmp = speed%100;
			if (tmp >= 50)
			speed += 100;
			printf("%u.%01u MHz", ((unsigned int) speed/1000),((unsigned int) (speed%1000)/100));
	     }
	}

	return;

}

int count_freq_stats(unsigned int cpu, unsigned int human)
{       
        int n = 0;
	unsigned long long total_time;
        struct cpufreq_stats *stats = cpufreq_get_stats(cpu, &total_time);
        
	while (stats) 
        { 
		if (human)
                {    
			                     
			n++;                    
	        }
                
	     stats = stats->next;

		if (stats)
		{
	
		}
             
       }
	cpufreq_put_stats(stats);
        
    return n;
}

/* --stats / -s */

void get_freq_stats(unsigned int cpu, unsigned int human, char (*arr)[][1000])
{       
        int j = 0;
	
	unsigned long long total_time;
        struct cpufreq_stats *stats = cpufreq_get_stats(cpu, &total_time);
        
	while (stats) 
        { 
		if (human)
                {    
                 
                  //printf("%5.1f",(100.0 * stats->time_in_state) / total_time);
                    sprintf((*arr)[j], "%5.1f",(100.0 * stats->time_in_state) / total_time);
			                     
			j++;                    
		  }
                
              else
                 {

	              //printf("%lu:%llu",stats->frequency, stats->time_in_state);
                      
                      print_speed(stats->frequency);
                      printf(" : %.2f%%",(100.0 * stats->time_in_state) / total_time);

	          }
	     stats = stats->next;
		if (stats)
		{
	
		}
             
       }
      
	cpufreq_put_stats(stats);
        
    
}


unsigned int count_cpus(void)
{
	FILE *fp;
	char value[LINE_LEN];
	unsigned int ret = 0;
	unsigned int cpunr = 0;

	fp = fopen("/proc/stat", "r");
	if (!fp) {
		printf(_("Couldn't count the number of CPUs (%s: %s), assuming 1\n"), "/proc/stat", strerror(errno));
		return 1;
	}

	while (!feof(fp)) {
		if (!fgets(value, LINE_LEN, fp))
			continue;
		value[LINE_LEN - 1] = '\0';
		if (strlen(value) < (LINE_LEN - 2))
			continue;
		if (strstr(value, "cpu "))
			continue;
		if (sscanf(value, "cpu%d ", &cpunr) != 1)
			continue;
		if (cpunr > ret)
			ret = cpunr;
	}
	fclose(fp);

	/* cpu count starts from 0, on error return 1 (UP) */
	return ret + 1;
}


