#include <sensor_structure.h>
#include <math.h>
#include <stdlib.h>
/**
 * Step 1 of Algorithm
 * @param no_sensor
 * @param p_sensor
 * @return
 */
//Step1 of algorithm
double **compute_support_degree_matrix(sensor_t *p_sensor,int no_sensor){
    //Declare dynamic 2D array
    double **D_array;

    //Allocating memory for rows=no_sensor
    D_array=(double **)malloc(sizeof(double *) * no_sensor);

    //Allocating memory for columns in each row
    for(int rows=0;rows<no_sensor;rows++){
        D_array[rows]= (double *)malloc(sizeof(double) * no_sensor);
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
            D_array[rows][cols]=exp(-fabs(temp_data));
        }
    }

    return D_array;
}
