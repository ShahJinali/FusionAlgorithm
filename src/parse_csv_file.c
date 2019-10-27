#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <parse_csv_file.h>

/**
 * @author:Jinali Shah
 * @version:1.2
 * @Date :2019/10/27
 * @param fptr
 * @param sensor
 * @return
 */
int parseFile(FILE *fptr, struct sensor_t *sensor) {
    char line[1024];
    char *token;
    int counter = 0;
    int sensor_data_counter = 1;
    int sensor_name_counter = 1;
    int sensor_time_counter = 1;

    while (fgets(line, 1024, fptr)) {

        token = strtok(line, ",");

        while (token != NULL) {
            if (sensor_time_counter == 1) {
                strcpy((sensor + counter)->time, token);
            } else if (sensor_name_counter == 2) {
                strcpy((sensor + counter)->name, token);
            } else if (sensor_data_counter == 3) {
                (sensor + counter)->data = atof(token);
            }
            token = strtok(NULL, ",");
            sensor_time_counter++;
            sensor_data_counter++;
            sensor_name_counter++;
        }
        counter++;
        //reset the counter
        sensor_name_counter = 1;
        sensor_data_counter = 1;
        sensor_time_counter = 1;
    }

    return 1;
}