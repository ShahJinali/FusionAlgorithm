#include <stdlib.h>
#include <sensor_structure.h>
#include <time_structure.h>
#include <string.h>
#include <time_list.h>

time_tt* get_time_list(sensor_t *p_sensor,int line_counter,int no_sensor_grp){

    /*
    Compute the length of time_list
    */
    int length_time_list=line_counter/no_sensor_grp;

    time_tt *p_time_list;
    /*
    Allocate the memory to pointer of type time_tt which is equal to no of unique time in csv file
    */
    p_time_list=(time_tt *)malloc(sizeof(time_tt) * length_time_list);

    char sensor_time[6];
    int time_counter=0;
    for(int i=0;i<line_counter;i+=no_sensor_grp){
        strcpy(sensor_time,(p_sensor+i)->time);
        p_time_list[time_counter]=time_parse(sensor_time,p_time_list[time_counter]);
        time_counter++;
    }
    return p_time_list;
}

/*
 * This function parses the string of type "1:20" and assign it to ype time_tt struct and also convert it into int value
 */
time_tt time_parse(char time[6],time_tt time1){
    char *token;
    char time_arr[6];
    int token_counter=1;

    strcpy(time_arr,time);
    token=strtok(time_arr,":");
    while(token != NULL){
        if(token_counter == 1)
        {
            time1.tm_hour=atoi(token);
        }else if(token_counter == 2)
        {
            time1.tm_min=atoi(token);
        }
        token = strtok(NULL, ":");
        token_counter++;
    }
    free(token);
    return time1;
}