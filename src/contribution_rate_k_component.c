#include <stdio.h>
#include <stdlib.h>

double *compute_contribution_K_rate(double *p_eigen_value,int no_sensor){
        double *p_alpha;
        p_alpha=(double *)malloc(sizeof(double) * no_sensor);

        /*
         * Step1 Compute the sum of eigen value
         */
        double sum_eigen_value =0.0;
        for(int i=0;i<no_sensor;i++){
            sum_eigen_value=sum_eigen_value+p_eigen_value[i];
        }
    /*
     * Step2 Compute alpha value
     */
        for(int i=0;i<no_sensor;i++){
            p_alpha[i]=p_eigen_value[i] / sum_eigen_value;
        }

        //return row matrix
        return p_alpha;

}