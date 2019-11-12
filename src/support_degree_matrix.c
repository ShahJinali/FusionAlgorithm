#include <stdio.h>
#include <sensor_structure.h>
#include <math.h>
#include <stdlib.h>

//Step1 of algorithm
double **compute_support_degree_matrix(sensor_t *p_sensor,int no_sensor){
    //Declare 2D array
    double **D_array;

    //Allocating memory for rows=no_sensor
    D_array=(double **)malloc(sizeof(double *) * no_sensor);

    //Allocating memory for columns in each row
    for(int rows=0;rows<no_sensor;rows++){
        D_array[rows]= (double *)malloc(sizeof(double) * no_sensor);
    }

    //compute matrix D
    for(int rows=0;rows<no_sensor;rows++){
        for(int cols=0;cols<no_sensor;cols++){
            double temp_data=((p_sensor+rows)->data)-((p_sensor+cols)->data);
            D_array[rows][cols]=exp(-fabs(temp_data));
        }
    }

    return D_array;
}
