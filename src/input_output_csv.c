#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sensor_structure.h>

/**
 * @param p_fptr pointer to input file
 * @param p_sensor pointer to typedef struct sensor_t
 * @return It return 1 on success
 * @details
     * The file pointer points to file specified by user as command line argument and cursor is set at the beginning of file.<br>
     * Outer while loop will read one line of file in each iteration.
     * fgets(line, 1024, p_fptr) reads one line of file at each iteration.<br>
     * For each iteration , it will store the time,name and data of sensor in sensor_t *sensor.<br>
     * To split the line , strtok() string tokenizer function is used which takes 2 parameter i.e the line itself and delimeter.
     * The comma "," is used as delimeter<br>
     * In total there will be 3 tokens for each line i.e. time,name and data but at a time only one token is read.<br>
     * The inner while is used for getting each token from a line.
     * After ,all the tokens are read from line, the sensor_counter is reset.
     * counter is incremented and next line is read.
 */
int read_csv(FILE *p_fptr, sensor_t *p_sensor) {
    char line[1024];
    char *token;
    int counter = 0;
    int sensor_counter=1;

    while (fgets(line, 1024, p_fptr)) {

        token = strtok(line, ",");

        while (token != NULL) {
            if (sensor_counter == 1) {
                strcpy((p_sensor + counter)->time, token);
            } else if (sensor_counter == 2) {
                strcpy((p_sensor + counter)->name, token);
            } else if (sensor_counter == 3) {
                (p_sensor + counter)->data = atof(token);
            }
            token = strtok(NULL, ",");
            sensor_counter++;
        }
        counter++;
        //reset the counter
        sensor_counter = 1;
    }
    /*
     * Free the Memory
     */
    free(token);
    return 1;
}