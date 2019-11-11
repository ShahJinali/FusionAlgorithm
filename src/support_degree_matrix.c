#include <stdio.h>
#include <sensor_structure.h>

double **compute_support_degree_matrix(sensor_t *p_sensor,int no_sensor){
    for (int i = 0; i < no_sensor; i++) {
        printf("The time is %s ", (p_sensor + i)->time);
        printf("The name is %s ", (p_sensor + i)->name);
        printf("The data is %lf ", (p_sensor + i)->data);
        printf("\n");
    }

}
