#ifndef FUSIONALGORITHM_UNIQUE_TIME_H
#define FUSIONALGORITHM_UNIQUE_TIME_H
#include <sensor_structure.h>
#include <time_structure.h>

time_tt* get_time_list(sensor_t *p_sensor,int line_counter,int length_time_list);
time_tt time_parse(char time[6],time_tt time1 );
int get_uniquetime_length(sensor_t *p_sensor,int line_counter);

#endif //FUSIONALGORITHM_UNIQUE_TIME_H
