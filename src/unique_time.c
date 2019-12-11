#include <stdlib.h>
#include <sensor_structure.h>
#include <time_structure.h>
#include <string.h>
#include <unique_time.h>

int strcontain(char *time,char **unique_time,int length_unique_time);

time_tt* get_time_list(sensor_t *p_sensor,int line_counter,int length_time_list){

    /*
    Compute the length of time_list
    */
    int no_sensor_grp=line_counter/length_time_list;

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

int get_uniquetime_length(sensor_t *p_sensor,int line_counter){

    /*
    *Declare the variable to store the length of 2D unique_time array
    * Declare the 2D array unique_time to store multiple unique strings
    */
    char **unique_time;
    unique_time=(char **)malloc(sizeof(char *) *line_counter);
    for(int i=0;i<line_counter;i++){
        unique_time[i]=(char *)malloc(sizeof(char) * 6);
    }

    /*
     * It is initialize to 1 because there will be at least one unique value and it increases as we find the another unique value
     */
    int length_unique_time=1;

    /*
    There will at least one unique string so 1st string is copied .
    */
     strcpy(unique_time[0],(p_sensor+0)->time);

    /*
     * The line_counter is declare as extern variable so ,
     * it is declare and defined in main.c as global variable but it's reference is used here
     * The loop will iterate till the end of .csv file to get the unique value of time
     * It internally calls strcontain() function which takes two argument i.e. current value of time from chosen line and array of unique_time
     * The strcontain() function return 1 if time value is present in unique_time
     * It return 0 if time value is not present in unique_time (which also means that time value is unique so add it in unique_time array)
     */
    for(int i=0;i<line_counter;i++){
        int result=strcontain((p_sensor+i)->time,unique_time,length_unique_time);
        //1 means true and 0 means false
        if(result == 0){
            strcpy(unique_time[length_unique_time],(p_sensor+i)->time);
            length_unique_time++;
        }
    }
    free(unique_time);
    return length_unique_time;
}
/*
 * This function strontain() return 1 if time value is present in unique_time 2D array else return 0.
 */
int strcontain(char *time,char **unique_time,int length_unique_time){
    int result;
    for(int j=0;j<length_unique_time;j++){
        result=strcmp(time,unique_time[j]);
        if(result == 0){
            return 1;
        }
    }
    return 0;
}