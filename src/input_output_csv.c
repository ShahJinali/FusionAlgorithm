/**
 * @file input_output_csv.c
 * @author Shah Jinali <jinalibenhiteshbhais@cmail.carleton.ca>
 * @author Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca>
 * @author Patel Jay <jpate122@uottawa.ca>
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sensor_structure.h>

/**
 * @param[in] p_fptr Pointer to input file
 * @param[out] p_sensor Pointer to typedef struct sensor_t
 * @return It return 1 on success
 * @brief This function read the .csv file pointed by p_fptr and store the time, name and data of sensor in struct p_sensor
 * @see sensor_structure.h
 */
int read_csv(FILE *p_fptr, sensor_t *p_sensor) {
    char line[1024];
    char *token;
    int counter = 0;
    int sensor_counter=1;

    /*
     * The file pointer points to file specified by user as command line argument and cursor is set at the beginning of file.<br>
     * Outer while loop will read one line of file in each iteration.
     * fgets(line, 1024, p_fptr) reads one line of file at each iteration.
     * For each iteration , it will store the time,name and data of sensor in sensor_t *sensor.
     * To split the line , strtok() string tokenizer function is used which takes 2 parameter i.e the line itself and delimeter.
     * The comma "," is used as delimeter
     * In total there will be 3 tokens for each line i.e. time,name and data but at a time only one token is read.
     * The inner while is used for getting each token from a line.
     * After ,all the tokens are read from line, the sensor_counter is reset; the counter is incremented and next line is read.
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
        /*
         * reset the counter
        */
         sensor_counter = 1;
    }
    /*
     * Free the Memory
     */
    free(token);
    return 1;
}

/**
 * @param[in] p_fptr
 * @param[in] p_sensor
 * @param[in] no_sensor
 * @param[in] fusedOutput
 * @return It will return 1 on success
 * @brief This function write the output of validate sensor and fused output to output file .The path of output file is data/output.txt.
 */
int write_output_file(FILE *p_fptr,sensor_t *p_sensor,int no_sensor, double fusedOutput){

    /*
     * Check if file pointer is initialize or not
     */
    if(p_fptr == NULL){
        printf("The file pointer is not initialize");
        return -1;
    }
    fprintf(p_fptr,"================AT TIME %s ==================\n",p_sensor->time);
    fputs("===========LIST OF VALIDATED SENSOR============\n", p_fptr);
    for (int i = 0; i < no_sensor; i++) {
        fprintf(p_fptr, "%s \t %lf\n", (p_sensor + i)->name, (p_sensor + i)->data);
    }
    fprintf(p_fptr, "The Fused Output is %lf \n\n", fusedOutput);

}