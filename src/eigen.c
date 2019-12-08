#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>
/**
 * This function computes the eigen value and eigen vector.
 * @param pp_D_aaray
 * @param p_eigen_val
 * @param pp_eigen_vec
 * @param no_sensor
 */
void compute_eigen(double **pp_D_aaray, double *p_eigen_val,double **pp_eigen_vec,int no_sensor){

    /*
     * Convert the 2D matrix pp_D_array into gsl matrix with dimension equal to no_sensor
     * Step1 Allocate the memory
     */
    gsl_matrix *p_matrix=gsl_matrix_alloc(no_sensor,no_sensor);

    /*
     * Step 2 Assign the value to gsl_matrix
     */
    for (int rows = 0; rows < no_sensor; rows++) {
        for (int cols = 0; cols < no_sensor; cols++) {
            gsl_matrix_set(p_matrix, rows, cols, pp_D_aaray[rows][cols]);
        }
    }
    /*
     * Step3 Allocate the temporary memory to eigen value equal to no_sensor
     */
    gsl_vector *p_eval = gsl_vector_alloc (no_sensor);

    /*
     * Step4 Allocate the temporary memory to eigen vector equal to no_sensor
     */
    gsl_matrix *p_evec = gsl_matrix_alloc (no_sensor, no_sensor);

    /*
     * Step5 Create the temporary eigen computation workspace
     */
    gsl_eigen_symmv_workspace * p_w = gsl_eigen_symmv_alloc (no_sensor);

    /*
     * Step6 Compute the eigen value and vector
     */
    gsl_eigen_symmv (p_matrix, p_eval, p_evec, p_w);

    /*
     * Step 7 Free the memory of workspace
     */
    gsl_eigen_symmv_free (p_w);

    /*
     * Step8 Arrange it in ascending order
     * change here
     */
    gsl_eigen_symmv_sort (p_eval, p_evec,GSL_EIGEN_SORT_ABS_DESC);

    /*
     *Step9 Assign the compute eval and evec to p_eigen_val,p_eigen_vec
     */
    for (int rows = 0; rows < no_sensor; rows++)
    {
        //assign the eigen value
        p_eigen_val[rows]= gsl_vector_get (p_eval, rows);

        //For getting the eigen vector and arrange it in row form instead of column form
        //change here if anything wrong
        for(int cols=0;cols<no_sensor;cols++){
            pp_eigen_vec[rows][cols]=gsl_matrix_get(p_evec, cols, rows);
        }
    }

    /*
     * Step 10 Free the eigen value and eigen vector
    */
     gsl_vector_free (p_eval);
    gsl_matrix_free (p_evec);

}
