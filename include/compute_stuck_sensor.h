#ifndef FUSIONALGORITHM_COMPUTE_STUCK_SENSOR_H
#define FUSIONALGORITHM_COMPUTE_STUCK_SENSOR_H
#include <sensor_structure.h>
#include <time_structure.h>

void stuck_sensor(sensor_t *p_sensor,time_tt *p_time_list,time_tt interval,int time_list_length,int no_sensor_grp);

#endif //FUSIONALGORITHM_COMPUTE_STUCK_SENSOR_H
