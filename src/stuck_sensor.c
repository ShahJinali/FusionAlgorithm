#include <sensor_structure.h>
#include <time_structure.h>
#include <stdlib.h>
#include <stdio.h>

time_tt time_diff(time_tt curr_time,time_tt next_time);

void compute_stuck_sensor(sensor_t *p_sensor,time_tt *p_time_list,time_tt interval,int time_list_length,int line_counter){

    int no_sensor_grp=line_counter/time_list_length;
    FILE *fptr;
    /*
     Open the file in write mode
     The file is generated in data/stuck_sensor.txt
     */
    fptr=fopen("../data/stuck_sensor.txt","w");
    if(fptr == NULL){
        printf("Error in creating the file");
    }

    int sensor_counter=0;

    for(int i=1;i<time_list_length;i++) {
        time_tt curr_time=p_time_list[i-1];
        time_tt next_time=p_time_list[i];
        time_tt diff=time_diff(curr_time,next_time);

        fputs("Time =\t",fptr);
        fprintf(fptr, "%d : %d\t", curr_time.tm_hour,curr_time.tm_min);
        fputs("Interval =\t",fptr);
        fprintf(fptr, "%d : %d\n", interval.tm_hour,interval.tm_min);
        fputs("===================================================\n",fptr);

        if((diff.tm_hour == interval.tm_hour) && (diff.tm_min == interval.tm_min)){

            for(int j=sensor_counter;j<sensor_counter+no_sensor_grp;j++){
                if((p_sensor+j) ->data == (p_sensor+(j+no_sensor_grp)) ->data){
                    fprintf(fptr," %s %s\n",(p_sensor+j)->name,"stuck");
                }
                else{
                    fprintf(fptr," %s %s\n",(p_sensor+j)->name,"Not stuck");
                }
            }
        }
        else{
            fputs("No sensor stuck\n",fptr);
        }
        sensor_counter=sensor_counter+no_sensor_grp;
        /*
        This condition is for the last time value
        Since it is last time value ,it will never get stuck
        */
        if(i == time_list_length -1){
            fputs("Time =\t",fptr);
            fprintf(fptr, "%d : %d\t", next_time.tm_hour,next_time.tm_min);
            fputs("Interval =\t",fptr);
            fprintf(fptr, "%d : %d\n", interval.tm_hour,interval.tm_min);
            fputs("===================================================\n",fptr);
            fputs("No sensor stuck\n",fptr);
        }

    }

}
/*
 * Does not consider the next day
 */
time_tt time_diff(time_tt curr_time,time_tt next_time){

    int diff_min;
    time_tt diff;
    diff_min=abs((next_time.tm_hour * 60+next_time.tm_min) - (curr_time.tm_hour * 60 +curr_time.tm_min));
    diff.tm_hour=diff_min / 60;
    diff.tm_min=diff_min % 60;
    return diff;
}

