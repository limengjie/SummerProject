#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_e_cnt(FILE * fp) {
        char line[1024];
        char * target = "mem-stores";
        int tot_count = 0, times = 0;
        int count = 0;
        char * token;
        char * count_str;

        while (fgets(line, 1024, fp)) {
                /*printf("%s \n", line);*/
                if (strstr(line, target)) {//if target str exists 
                        count = lnToNum(line);
                        tot_count += count;
                        times++;
                        printf("time = %d, count = %d\n", times, count);
                }
        }
        if (tot_count != 0 && times != 0) {
                /*[>delete the last count to get a more accurate result<]*/
                /*tot_count -= count;*/
                /*times--;*/

                printf("total count = %d\n", tot_count);
                printf("times = %d\n", times);

                /*get a mean value*/
                count = get_mean(tot_count, times);
        }


        return count;
}

int lnToNum(char * line) {
        char * token, * count_str;
        int count;

        /*get count in string*/
        token = strtok(line, " \t\n");
        count_str = strtok(NULL, " \t\n");
        /*printf("count = %s\n", count_str);*/

        /*convert string to integer*/
        count = my_atoi(count_str);

        return count;
}

int get_mean(int total, int times) {
        return total/times;
}

int add_latency(int ori_latency) {
        /*calculate according to the goal*/
        return ori_latency * 100;
}

int my_atoi(char * num_str) {
        int num = 0, i;
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
        int count;
        count = get_e_cnt(fp);
        printf("average count = %d\n", count);


        /*add latency */
        int res;
        res = add_latency(count);
        printf("the final result = %d\n", res);


        /*close file*/
        fclose(fp);

        return 0;
}


