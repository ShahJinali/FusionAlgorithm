#ifndef FUSIONALGORITHM_INPUT_OUTPUT_CSV_H
#define FUSIONALGORITHM_INPUT_OUTPUT_CSV_H
#include <sensor_structure.h>
/**
 * @brief  In order to use this function, include <input_output_csv.h> header file in your code.
 * @details This function parse the .csv file and store the data in struct.The implementation detail and
 * the working of this function is explained in <input_output_csv.c> file
 */
int read_csv(FILE *p_fptr, sensor_t *p_sensor);

#endif //FUSIONALGORITHM_INPUT_OUTPUT_CSV_H
