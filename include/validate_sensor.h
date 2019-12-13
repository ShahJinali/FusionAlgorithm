#ifndef FUSIONALGORITHM_VALIDATE_SENSOR_H
#define FUSIONALGORITHM_VALIDATE_SENSOR_H
#include <stdio.h>
#include <sensor_structure.h>
#include <time_structure.h>

//Return the name of sensor which is out of prescribed range
int compare_sensor_range(sensor_t *p_sensor,double min ,double max,int line_counter,time_tt curr_time,sensor_t *v_sensor);
#endif //FUSIONALGORITHM_VALIDATE_SENSOR_H
