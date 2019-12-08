#include <sensor_structure.h>
#include <stdlib.h>
#include <string.h>
#include <unique_value.h>

extern int line_counter;
int strcontain(char *time,char **unique_time,int length_unique_time);

/**
 * This function returns the unique value of time from char** arr
 * @param p_sensor
 * @return
 */
int struniquetime(sensor_t *p_sensor,char ** unique_time){

    //Declare the 2D array unique_time to store multiple unique strings
    //char **unique_time;

    /*
     *Declare the variable to store the length of 2D unique_time array
     * It is initialize to 1 because there will be at least one unique value and it increases as we find the another unique value
     */
    int length_unique_time=1;

    //There will at least one unique string so 1st string is copied .
    strcpy(unique_time[0],(p_sensor+0)->time);

    //For each time of p_sensor structure
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
            unique_time=(char **)realloc(unique_time,sizeof(char *) * 1);
            unique_time[length_unique_time]=(char *)malloc(sizeof(char) * 6);
            strcpy(unique_time[length_unique_time],(p_sensor+i)->time);
            length_unique_time++;
        }
    }
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
