#include <sensor_structure.h>
#include <math.h>
#include <stdlib.h>

/**
 * <p>This function computes the support degree matrix which is the first step of sensor fusion algorithm</p>
 * Step 1 of Algorithm
 * @param no_sensor
 * @param p_sensor
 * @return
 * @version 1.0
 */
double **compute_support_degree_matrix(sensor_t *p_sensor,int no_sensor){
    /*
    * Declare dynamic 2D array
    */
     double **pp_D_array;

    /*
    * Allocating memory for rows=no_sensor
    */
     pp_D_array=(double **)malloc(sizeof(double *) * no_sensor);

    /*
    * Allocating memory for columns in each row
    */
     for(int rows=0;rows<no_sensor;rows++){
        pp_D_array[rows]= (double *)malloc(sizeof(double) * no_sensor);
    }

    /*
     * Compute matrix D
     * 1.Compute temp_data
     * 2.Compute absolute of temp_data using fabs() function
     * 3.Compute exponential using exp()
     */
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++){
            double temp_data=((p_sensor+rows)->data)-((p_sensor+cols)->data);
            pp_D_array[rows][cols]=exp(-fabs(temp_data));
        }
    }
    return pp_D_array;
}
