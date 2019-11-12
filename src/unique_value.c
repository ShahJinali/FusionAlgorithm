#include <sensor_structure.h>
#include <stdlib.h>
#include <string.h>
#include <unique_value.h>

int strcontain(char *time,char **unique_time,int length_unique_time);

char** strunique(sensor_t *p_sensor){

    char **unique_time;
    int length_unique_time=1;
    //Allocating memory of one word initially
    unique_time=(char **)malloc(sizeof(char *) * 1);

    //Allocating memory of one word = 6 characters
    unique_time[0]=(char *)malloc(sizeof(char) * 6);

    strcpy(unique_time[0],(p_sensor+0)->time);

    //For each time of p_sensor structure
    for(int i=0;i<6;i++){
        int result=strcontain((p_sensor+i)->time,unique_time,length_unique_time);
        //1 means true and 0 means false
        if(result == 0){
            unique_time=(char **)realloc(unique_time,sizeof(char *) * 1);
            unique_time[length_unique_time]=(char *)malloc(sizeof(char) * 6);
            strcpy(unique_time[length_unique_time],(p_sensor+i)->time);
            length_unique_time++;
        }
    }
    return unique_time;
}

int struniquelen(sensor_t *p_sensor){

    char **unique_time;
    int length_unique_time=1;
    //Allocating memory of one word initially
    unique_time=(char **)malloc(sizeof(char *) * 1);

    //Allocating memory of one word = 6 characters
    unique_time[0]=(char *)malloc(sizeof(char) * 6);

    strcpy(unique_time[0],(p_sensor+0)->time);

    //For each time of p_sensor structure
    for(int i=0;i<6;i++){
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
