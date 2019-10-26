#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parse_csv_file.h>

int parseFile(FILE * fptr,char ** sensor_time,char ** sensor_name,double * sensor_data){
    char line[1024];
    char *token;
    int counter = 0;
    int sensor_data_counter = 1;
    int sensor_name_counter = 1;
    int sensor_time_counter = 1;

    while (fgets(line, 1024, fptr)) {

        sensor_time[counter]=(char *)malloc(6* sizeof(char));
        sensor_name[counter] = (char *) malloc(30 * sizeof(char));
        token = strtok(line, ",");

        while (token != NULL) {
            if(sensor_time_counter ==1 ){
                strcpy(sensor_time[counter],token);
            } else if (sensor_name_counter == 2) {
                strcpy(sensor_name[counter],token);
            } else if (sensor_data_counter == 3) {
                sensor_data[counter] = atof(token);
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
        sensor_time_counter=1;
    }

    return 1;
}