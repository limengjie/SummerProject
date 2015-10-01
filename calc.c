#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_line(FILE * fp, char * target, char * line) {
        char * fgetsRtn;

        while (fgets(line, 1024, fp)) {
                /*printf("%s \n", line);*/
                if (strstr(line, target)) //if target str exists 
                       return;
        }
}

int get_e_cnt(char * line) {
        int count;
        char * token;
        char * count_str;

        /*get count in string*/
        token = strtok(line, " \t\n");
        while (token != NULL) {
                count_str = token;
                /*printf("%s\n", token);*/
                token = strtok(NULL, " \t\n");
        }
        /*printf("%s\n", count_str);*/


        /*convert string to integer*/
        count = atoi(count_str);

        return count;
}

int add_latency(int ori_latency) {
        /*calculate according to the goal*/
        return ori_latency * 100;
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


        /*find the line including the event count*/
        char line[1024];
        char * target = "Event count";
        get_line(fp, target, line);
        /*printf("%s", line);*/
        
        
        /*get the event count*/
        int count;
        count = get_e_cnt(line);
        printf("count = %d\n", count);


        /*add latency */
        int res;
        res = add_latency(count);
        printf("the final result = %d\n", res);

        return 0;
}


