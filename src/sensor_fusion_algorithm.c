#include <sensor_fusion_algorithm.h>
#include <stdio.h>
#include <support_degree_matrix.h>
#include <eigen.h>
#include <stdlib.h>
#include <principal_component.h>

double sensor_fusion(sensor_t *p_sensor,int no_sensor){

    double **pp_D_array;
    //Call Step1 of Algorithm
    pp_D_array=compute_support_degree_matrix(p_sensor,no_sensor);

    //Call Step2 of Algorithm
    double *p_eigen_val;
    double **pp_eigen_vector;

    p_eigen_val=(double *)malloc(sizeof(double) * no_sensor);

    pp_eigen_vector=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_eigen_vector[i]=(double *) malloc(sizeof(double) * no_sensor);
    }

    compute_eigen(pp_D_array,p_eigen_val,pp_eigen_vector,no_sensor);

    /*
     * Call the step 3 of Algorithm
     */
    double **pp_y_principal_component;
    //Memory Allocation for each row
    pp_y_principal_component=(double **)malloc(sizeof(double *) *no_sensor);
    //Memory allocation for each column for each row
    for(int i=0;i<no_sensor;i++){
        pp_y_principal_component[i]=(double *)malloc(sizeof(double) *no_sensor);
    }

    pp_y_principal_component=compute_principal_component(pp_eigen_vector,pp_D_array,no_sensor);

    /*
     * Call the step4 of Algorithm
     */
    return 20;
}