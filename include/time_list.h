#ifndef FUSIONALGORITHM_TIME_LIST_H
#define FUSIONALGORITHM_TIME_LIST_H
#include <sensor_structure.h>
#include <time_structure.h>

time_tt* get_time_list(sensor_t *p_sensor,int line_counter,int no_sensor_grp);
time_tt time_parse(char time[6],time_tt time1 );
#endif //FUSIONALGORITHM_TIME_LIST_H
