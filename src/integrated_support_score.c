#include <stdio.h>
#include <stdlib.h>

double *compute_integrated_score(double *p_alpha,double **pp_y_value,int no_sensor,int m){

    double *p_Z;
    /*
     * Allocate the memory to pointer p_Z
     */
    p_Z=(double *)malloc(sizeof(double) * no_sensor);

    /*
     * Compute *p_Z which is equal to  (*p_alpha) * (**pp_y_value) and iterate it to take first m elements
     */
    for(int i=0;i<no_sensor;i++){
        p_Z[i]=0;
        for(int j=0;j<m;j++){
                p_Z[i]=p_Z[i]+(p_alpha[j] * pp_y_value[j][i]);
        }
    }
    return p_Z;
}
