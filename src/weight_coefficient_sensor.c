#include <stdlib.h>
#include <stdio.h>
#include <sensor_structure.h>

double weight_coefficient(sensor_t *p_sensor, double *p_Z ,int *p_discard_index,int no_sensor){

    /*
     * Calculate the Z_sum for value with p_discard_index = 0
     */
    double Z_sum=0;
    /*
     * Variable to count no of 0's
    */
     int index_counter=0;
    for(int i=0;i<no_sensor;i++){
        if(p_discard_index[i] == 0){
            Z_sum=Z_sum+p_Z[i];
            index_counter++;
        }
    }
//    printf("Index counter = %d\n",index_counter);
    /*
     * Calculate the weight coefficient factor for value with p_discard_index =0
     */
    double *p_weight_coefficient=(double *)malloc(sizeof(double) * index_counter);
    int internal_counter=0;

    for(int i=0;i<no_sensor;i++){
        if(p_discard_index[i] == 0){
            p_weight_coefficient[internal_counter]=p_Z[i] /Z_sum;
            internal_counter++;
        }
    }

    internal_counter=0;
    /*
     * Create the dynamic array p_sensor__value for p_discard_index == 0
     */
    double *p_sensor_value=(double *)malloc(sizeof(double) * index_counter);
    for(int i=0;i<no_sensor;i++){
        if(p_discard_index[i] == 0){
            p_sensor_value[internal_counter]=(p_sensor+i)->data;
            internal_counter++;
        }
    }

    double fused_output=0;
    for(int i=0;i<index_counter;i++){
        fused_output=fused_output+(p_sensor_value[i] * p_weight_coefficient[i]);
    }

    /*
     * free the memory
     */
    free(p_sensor_value);
    free(p_weight_coefficient);
    return fused_output;
}