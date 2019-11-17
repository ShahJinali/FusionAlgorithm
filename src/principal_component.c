#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <stdlib.h>

double **compute_principal_component(double **pp_eigen_vector,double **pp_D_array,int no_sensor){

    double **pp_principal_component;
    //Memory Allocation for each row
    pp_principal_component=(double **)malloc(sizeof(double *) *no_sensor);
    //Memory allocation for each column for each row

    for(int i=0;i<no_sensor;i++){
        pp_principal_component[i]=(double *)malloc(sizeof(double) *no_sensor);
    }

    //Step1 Of Algorithm ,Allocate the memory to gsl_matrix
    gsl_matrix *p_eigen_vec=gsl_matrix_alloc(no_sensor,no_sensor);
    gsl_matrix *p_support_degree=gsl_matrix_alloc(no_sensor,no_sensor);
    gsl_matrix *p_y=gsl_matrix_alloc(no_sensor,no_sensor);

    //Step2 Of Algorithm Convert the 2D array into GSL Matrix
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++){
            gsl_matrix_set(p_eigen_vec,rows,cols,pp_eigen_vector[rows][cols]);
            gsl_matrix_set(p_support_degree,rows,cols,pp_D_array[rows][cols]);
            gsl_matrix_set(p_y,rows,cols,0.0);
        }
    }

    //Step3 of ALgorithm compute matrix multiplication of p_y = p_eigen_vector * p_support_degree
    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                    1.0, p_eigen_vec,p_support_degree,
                    0.0, p_y);

    //Step4 Convert gsl_matrix to 2-D array
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++){
            pp_principal_component[rows][cols]=gsl_matrix_get(p_y,rows,cols);
        }
    }

    return pp_principal_component;
}