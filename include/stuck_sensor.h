#ifndef FUSIONALGORITHM_STUCK_SENSOR_H
#define FUSIONALGORITHM_STUCK_SENSOR_H
#include <sensor_structure.h>
#include <time_structure.h>

void compute_stuck_sensor(sensor_t *p_sensor,time_tt *p_time_list,time_tt interval,int time_list_length,int no_sensor_grp);

#endif //FUSIONALGORITHM_STUCK_SENSOR_H
