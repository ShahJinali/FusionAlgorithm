#include <time_structure.h>
#include <sensor_structure.h>
#include <stdio.h>
#include <unique_time.h>
#include <string.h>

int compare_sensor_range(sensor_t *p_sensor,double min ,double max,int line_counter,time_tt curr_time,sensor_t *v_sensor){

    int length=0;
    for(int i=0; i < line_counter; i++) {
        time_tt time;
        time=time_parse((p_sensor + i)->time,time);
        if((time.tm_hour == curr_time.tm_hour) && (time.tm_min == curr_time.tm_min)) {

            if (min <= ((p_sensor + i)->data) && ((p_sensor + i)->data) <= max) {
                strcpy((v_sensor + length)->time, (p_sensor + i)->time);
                strcpy((v_sensor + length)->name, (p_sensor + i)->name);
                (v_sensor + length)->data = (p_sensor + i)->data;
                length++;
            } else {
                if (!(p_sensor + i)->time) {
                    break;
                } else
                    continue;
            }
        }
    }
    return length;
}
