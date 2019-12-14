#include <sensor_fusion_algorithm.h>
#include <stdio.h>
#include <support_degree_matrix.h>
#include <eigen.h>
#include <stdlib.h>
#include <principal_component.h>
#include <contribution_rate_k_component.h>
#include <contribution_rate_m_component.h>
#include <integrated_support_score.h>
#include <eliminate_incorrect_data.h>
#include <weight_coefficient_sensor.h>

double sensor_fusion(sensor_t *p_sensor,int no_sensor){

    int m;
    double **pp_D_array;
    //Call Step1 of Algorithm
    pp_D_array=compute_support_degree_matrix(p_sensor,no_sensor);
    printf("==========================================The step1 of an algorithm=================================\n");
    for(int i=0;i<no_sensor;i++){
        for(int j=0;j<no_sensor;j++){
            printf("%lf ",pp_D_array[i][j]);
        }
        printf("\n");
    }

    //Call Step2 of Algorithm
    double *p_eigen_val;
    double **pp_eigen_vector;

    p_eigen_val=(double *)malloc(sizeof(double) * no_sensor);

    pp_eigen_vector=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_eigen_vector[i]=(double *) malloc(sizeof(double) * no_sensor);
    }

    compute_eigen(pp_D_array,no_sensor,p_eigen_val,pp_eigen_vector);
    printf("======================================The step 2 of an algorithm=======================================\n");
    for(int i=0;i<no_sensor;i++){
        printf("The eigen value is %lf : [ ",p_eigen_val[i]);
        for(int j=0;j<no_sensor;j++){
            printf("%lf ,",pp_eigen_vector[i][j]);
        }
        printf("\b ]\n");
    }

    /*
     * Call the step 3 of Algorithm
     */
    double **pp_y_principal_component;
    pp_y_principal_component=compute_principal_component(pp_eigen_vector,pp_D_array,no_sensor);
    printf("====================================Step3 of Algorithm======================================\n");
    for(int i=0;i<no_sensor;i++){
        for(int j=0;j<no_sensor;j++){
            printf("%lf ",pp_y_principal_component[i][j]);
        }
        printf("\n");
    }

    /*
     * Call the step4 of Algorithm
     */
    printf("=========================================Step 4 of Algorithm============================================ \n");
    double * p_alpha;
    p_alpha=compute_contribution_K_rate(p_eigen_val,no_sensor);
    printf("[ ");
    for(int i=0;i<no_sensor;i++){
        printf("%lf ,",p_alpha[i]);
    }
    printf("\b] \n");

    /*
     * Call step5 of algorithm
     */
    printf("========================================Step5 of Algorithm====================================\n");
    m=compute_contribution_M_rate(p_alpha,no_sensor,0.85);
    printf("The value of m is %d\n",m);

    /*
     * Call step 6 of algorithm
     */
    printf("=====================================Step 6 of Algorithm=====================================\n");
    double *p_Z;
    p_Z=compute_integrated_score(p_alpha,pp_y_principal_component,no_sensor,m);
    printf("[ ");
    for(int i=0;i<no_sensor;i++){
        printf("%lf ,",p_Z[i]);
    }
    printf("\b]\n ");

    /*
     * Call Step7(1) of an algorithm
     */
    printf("===========================================Step7(1) of Algorithm==========================================\n");
    int *p_discard_index=eliminate_data(p_Z,0.7,no_sensor);
    for(int i=0;i<no_sensor;i++){
        printf("%d ",p_discard_index[i]);
    }

    /*
     * Call Step7(2) of an algorithm
     */
    printf("\n===========================================Step7(2 & 3) of Algorithm==========================================\n");
    double fused_output=weight_coefficient(p_sensor,p_Z,p_discard_index,no_sensor);
    printf("%lf ",fused_output);

    /*
     * Free the memory
     */
    free(pp_D_array);
    free(p_eigen_val);
    free(pp_eigen_vector);
    free(pp_y_principal_component);
    free(p_alpha);
    free(p_Z);
    free(p_discard_index);
    return fused_output;
}