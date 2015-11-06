#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DRAM_W_LATENCY 60
#define NVM_W_LATENCY 150

/*typedef long long unsigned int*/

unsigned long long get_e_cnt(FILE * fp) {
        char line[1024];
        char * target = "mem-stores";
        int times = 0;
        unsigned long long tot_count = 0; 
        unsigned long long count = 0;
        char * token;
        char * count_str;

        while (fgets(line, 1024, fp)) {
                /*printf("%s \n", line);*/
                if (strstr(line, target)) {//if target str exists 
                        count = (unsigned long long) strToNum(line);
                        tot_count += count;
                        times++;
                        /*printf("time = %d, count = %d\n", times, count);*/
                }
        }
        if (tot_count != 0 && times != 0) {
                /*[>delete the last count to get a more accurate result<]*/
                /*tot_count -= count;*/
                /*times--;*/

                /*printf("total count = %llu\n", tot_count);*/
                printf("times = %d\n", times);

                /*[>get a mean value<]*/
                /*count = get_mean(tot_count, times);*/
        }


        return tot_count;
}

int strToNum(char * line) {
        char * token;
        char * count_str;
        /*int count;*/

        /*if option is -I*/
        /*get count in string*/
        token = strtok(line, " \t\n");
        count_str = strtok(NULL, " \t\n");
        printf("count = %s\n", count_str);

        /*if option is -r*/
        /*count_str = strtok(line, " \t\n");*/

        /*convert string to llu*/
        int cnt = perf_atollu(count_str);

        return cnt;
}

/*int get_mean(int total, int times) {*/
        /*return total/times;*/
/*}*/

unsigned long long add_latency(unsigned long long  orig_latency) {
        /*calculate according to the goal*/
        unsigned long long diff = NVM_W_LATENCY - DRAM_W_LATENCY;
        return diff * orig_latency;
}

int perf_atollu(char * num_str) {
        int num = 0; 
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
        count = get_e_cnt(fp);
        printf("total count = %llu\n", count);


        /*add latency */
        unsigned long long res;
        res = add_latency(count);
        printf("the final result = %llu\n", res);


        /*close file*/
        fclose(fp);

        return 0;
}


