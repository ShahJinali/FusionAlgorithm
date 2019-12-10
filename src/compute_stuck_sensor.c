#include <sensor_structure.h>
#include <time_structure.h>
#include <stdlib.h>
#include <stdio.h>

time_tt time_diff(time_tt curr_time,time_tt next_time);

void stuck_sensor(sensor_t *p_sensor,time_tt *p_time_list,time_tt interval,int time_list_length,int no_sensor_grp){
    int sensor_counter=0;

    for(int i=1;i<time_list_length;i++) {
        time_tt curr_time=p_time_list[i-1];
        time_tt next_time=p_time_list[i];
        time_tt diff=time_diff(curr_time,next_time);

        if((diff.tm_hour == interval.tm_hour) && (diff.tm_min == interval.tm_min)){
            printf("Inside if\n");
            for(int j=sensor_counter;j<sensor_counter+no_sensor_grp;j++){

                if((p_sensor+j) ->data == (p_sensor+(j+no_sensor_grp)) ->data){
                    printf("%s ",(p_sensor+j)->name);
                }
            }
        }
        sensor_counter=sensor_counter+no_sensor_grp;
        printf("\n");
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

