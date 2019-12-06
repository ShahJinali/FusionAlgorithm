#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int *eliminate_data(double *p_Z,double fault_value,int no_sensor){

    /*
     * Eliminate the incorrect data
     * Find the index of sensor which doesn't satisfy the given equation in paper with fault tolerance specified by the user
     */

    double Z_sum=0;
    /*
     * Initialize the the array of discarded index with 0 .
     */
    int *p_discard_index;
    p_discard_index=(int *)calloc(no_sensor, sizeof(int));

    /*
     * Compute Z_sum
     */
    for(int i=0;i<no_sensor;i++){
        Z_sum=Z_sum+p_Z[i];
    }
//    printf("The sum is %lf \n",Z_sum);

    double comparable_value= fabs(Z_sum/no_sensor) * fault_value;
//    printf("The comp val is %lf \n",comparable_value);
    /*
     * Find the sensor to be eliminated.If the particular sensor is eliminated then set the corresponding discarded_index to 1.
     * Error If p_Z is satisfied then that sensor should be discarded
     * To be discarded is set to 1
     */
    for(int i=0;i<no_sensor;i++){
 //       printf("p_z and com val are %lf %lf\n",fabs(p_Z[i]), comparable_value);
        if(fabs(p_Z[i]) < comparable_value){
            p_discard_index[i] =1;
        }
    }
    return p_discard_index;
}
