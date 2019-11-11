#include <sensor_fusion_algorithm.h>
#include <stdio.h>
#include <support_degree_matrix.h>

double sensor_fusion(sensor_t *p_sensor,int no_sensors){

    compute_support_degree_matrix(p_sensor,no_sensors);
    return 20;
}