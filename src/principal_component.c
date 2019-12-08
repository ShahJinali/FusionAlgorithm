#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <stdlib.h>

/**
 *<p>
 * @param pp_eigen_vector
 * @param pp_D_array
 * @param no_sensor
 * @return
 * @version 1.0
 *
 */
double **compute_principal_component(double **pp_eigen_vector,double **pp_D_array,int no_sensor){

    double **pp_principal_component;
    /*
    Memory Allocation for each row
    */
     pp_principal_component=(double **)malloc(sizeof(double *) *no_sensor);

     /*
     Memory allocation for each column of each row
    */
    for(int i=0;i<no_sensor;i++){
        pp_principal_component[i]=(double *)malloc(sizeof(double) *no_sensor);
    }

    /*
    Allocate the memory to gsl_matrix which is equal to (no_sensor,so_sensor)
    */
    gsl_matrix *p_eigen_vec=gsl_matrix_alloc(no_sensor,no_sensor);
    gsl_matrix *p_support_degree=gsl_matrix_alloc(no_sensor,no_sensor);
    gsl_matrix *p_y=gsl_matrix_alloc(no_sensor,no_sensor);

    /*
    Convert the 2D array into GSL Matrix
    */
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++)
        {
            gsl_matrix_set(p_eigen_vec,rows,cols,pp_eigen_vector[rows][cols]);
            gsl_matrix_set(p_support_degree,rows,cols,pp_D_array[rows][cols]);
            gsl_matrix_set(p_y,rows,cols,0.0);
        }
    }

    /*
     Compute the matrix multiplication of p_y = p_eigen_vector * p_support_degree using the predefined function available in GSL.
    */
     gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                    1.0, p_eigen_vec,p_support_degree,
                    0.0, p_y);

    /*
    Convert the product obtained i.e. p_y  back to 2-D array which is stored in pp_principal_component
    */
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++)
        {
            pp_principal_component[rows][cols]=gsl_matrix_get(p_y,rows,cols);
        }
    }
    return pp_principal_component;
}