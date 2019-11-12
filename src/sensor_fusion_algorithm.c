#include <sensor_fusion_algorithm.h>
#include <stdio.h>
#include <support_degree_matrix.h>

double sensor_fusion(sensor_t *p_sensor,int no_sensor){

    double **D_array;
    //Call Step1 of Algorithm
    D_array=compute_support_degree_matrix(p_sensor,no_sensor);

    //print no of sensor
    //printf("%d\n",no_sensor);

    //printing the 2D array
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++){
            printf("%lf\t",D_array[rows][cols]);
        }
        printf("\n");
    }

    return 20;
}