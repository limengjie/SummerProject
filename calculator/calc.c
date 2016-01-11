#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DRAM_W_LATENCY 60
#define NVM_W_LATENCY 150
#define NUMA 10


void strToNum(char * line, char * count_str) {
        /*perf cmd format: perf stat -I ... -e ...*/
        /*example:*/
        /*  time       counts      unit events*/
        /*0.100006197    95         mem-stores*/
        /*The output stat derived from the cmd above can be */
        /*parsed by this function.*/

        char * token;
        char * str;
        /*int count;*/

        /*if option is -I*/
        /*get count in string*/
        token = strtok(line, " \t\n");
        str = strtok(NULL, " \t\n");
        int i;
        for(i = 0; str[i] != '\0'; ++i)
                count_str[i] = str[i];
        count_str[i] = '\0';

        /*printf("count = %s\n", count_str);*/
}

float get_time(char * line) {
        float time;
        char * time_str;

        time_str = strtok(line, " \t\n");
        /*printf("time = %s\n", time_str);*/

        time = atof(time_str);
        /*printf("float time = %f\n", time);*/

        return time;

}

float add_latency(unsigned long long  orig_latency, float * time) {
        /*calculate the extra latency based on the # of mem writes*/
        unsigned long long diff = NVM_W_LATENCY - DRAM_W_LATENCY;
        float tot_time;
        float additional_time = diff*orig_latency; 

        /*printf("original lat = %llu\n", orig_latency);*/
        
        /*divide by 1,000,000,000, the unit is second*/
        int i;
        for (i = 0; i < 9; ++i)
                additional_time /= 10;
        /*printf("additional time = %f\n", additional_time);*/
        tot_time = *time + additional_time;

        return tot_time + NUMA;
}

unsigned long long perf_atollu(char * num_str) {
        unsigned long long num = 0; 
        int i;
        for (i = 0; i < strlen(num_str); ++i) {
                if (num_str[i] == ',')
                        continue;
                else {
                        num = (num*10 + num_str[i] - '0');
                        /*printf("%d : %d\n", i, num);*/
                }
        }

        return num;
}


void get_e_cnt(FILE * fp, unsigned long long * tot_count, float * time) {
        char line[1024];
        char * target = "mem-stores";
        int times = 0;
        unsigned long long count = 0;
        char * token;
        char count_str[100];

        *tot_count = 0;

        /*parse each line*/
        while (fgets(line, 1024, fp)) {
                /*printf("%s \n", line);*/
                if (strstr(line, target)) {//if target str exists 
                        strToNum(line, count_str);
                        /*printf("count_str = %s\n", count_str);*/
                        count = perf_atollu(count_str);
                        *tot_count += count;
                        times++;
                        /*printf("time = %d, count = %d\n", times, count);*/
                }
        }

        /*parse the last line to get the live time of this process*/
        *time = get_time(line);
}

int main(int argc, char * argv[]) {
        if (argc != 2) {
                fprintf(stderr, "Usage: calc [filename]\n");
                exit(-1);
        }


        /*open the file*/
        char * infile = argv[1];
        FILE * fp;
        if((fp = fopen(infile, "r")) == NULL) {
                fprintf(stderr, "No such file.\n");
                exit(-1);
        }
        /*printf("Open %s successfully.\n", infile);*/


        /*get the event count*/
        unsigned long long count;
        float time;
        get_e_cnt(fp, &count, &time);
        /*printf("total count = %llu\n", count);*/
        /*printf("time = %f\n", time);*/


        /*add latency */
        float res;
        res = add_latency(count, &time);
        /*print the final result*/
        printf("%f\n", res);


        /*close file*/
        fclose(fp);

        return 0;
}


