#ifndef FUSIONALGORITHM_EIGEN_H
#define FUSIONALGORITHM_EIGEN_H
/**
 * @brief  In order to use this function, include <eigen.h> header file in your code.
 * @details This function computes the eigen value and eigen vector for symmetric matrix.The implementation detail and
 * the working of this function is explained in <eigen.c> file
 */
int compute_eigen(double **pp_D_array,int no_sensor, double *p_eigen_val,double **pp_eigen_vec);
#endif //FUSIONALGORITHM_EIGEN_H
