#ifndef FUSIONALGORITHM_WEIGHT_COEFFICIENT_SENSOR_H
#define FUSIONALGORITHM_WEIGHT_COEFFICIENT_SENSOR_H
#include <stdio.h>
#include <sensor_structure.h>

double weight_coefficient(sensor_t *p_sensor, double *p_Z ,int *p_discard_index,int no_sensor);

#endif //FUSIONALGORITHM_WEIGHT_COEFFICIENT_SENSOR_H
