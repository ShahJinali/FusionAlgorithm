#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <input_output_csv.h>

/**
 * @author:Jinali Shah
 * @version:1.1
 * @Date :2019/10/27
 * @param p_fptr
 * @param p_sensor
 * @return
 */
int read_csv(FILE *p_fptr, sensor_t *p_sensor) {
    char line[1024];
    char *token;
    int counter = 0;
    int sensor_counter=1;

    /*
     * The file pointer points to sample.csv file  and cursor is set at the beginning of file.
     * Outer while loop will read one line of file in each iteration.
     * fgets(line, 1024, p_fptr) reads one line of file at each iteration.
     * For each iteration , it will store the time,name and data of sensor in sensor_t *sensor.
     * To split the line , strtok() string tokenizer function is used which takes 2 parameter i.e the line itself and delimeter.
     * In total there will be 3 tokens for each line i.e. time,name and data but at a time only one token is read.
     * So, inner while is used for getting each token from a line.
     * To store the token in respective data type of struct, 3 internal counters are used.
     * After ,all the tokens are read from line, the internal counters are reset.
     * Loop counter is incremented and next line is read.
     */
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

    return 1;
}