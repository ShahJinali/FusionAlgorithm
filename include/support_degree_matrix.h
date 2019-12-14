#ifndef FUSIONALGORITHM_SUPPORT_DEGREE_MATRIX_H
#define FUSIONALGORITHM_SUPPORT_DEGREE_MATRIX_H
#include <sensor_structure.h>
/**
 * @brief  In order to use this function, include <support_degree_matrix.h> header file in your code.
 * @details This function computes the support degree of defined matrix.The implementation detail and
 * the working of this function is explained in <support_degree_matrix.c> file
 */
double **compute_support_degree_matrix(sensor_t *p_sensor,int no_sensor);

#endif //FUSIONALGORITHM_SUPPORT_DEGREE_MATRIX_H
