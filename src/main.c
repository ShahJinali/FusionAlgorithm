#include <stdio.h>
#include <stdlib.h>
#include <parse_csv_file.h>

/**
 * @author : Jinali Shah
 * @version:1.1
 * @date :2019/10/27
 * @return
 *  <p>This is main function and executable file will run this function</p>
 */

int main() {

    struct sensor_t *sensor;
    /**
        This is the pointer to file sample.csv.The file sample.csv is open in read mode
     */
    FILE *fptr;
    char line[1024];
    int line_counter = 0;
    int result;
    fptr = fopen("../sample.csv", "r");

    /**
     * If file is not found in specified path ,then it will return -1 and exit the program
     */
    if (fptr == NULL) {
        printf("The file pointer is not initialize");
        return -1;
    }
    /*
    * This loop is used to read the number of lines of file.So it can be further used to initialize the dynamic
     * array of struct sensor_t *sensor
    */
    while (fgets(line, 1024, fptr)) {
        line_counter++;
    }

    /*
     * Set the cursor at the beginning of file
     */
    fseek(fptr, 0, 0);

    /*
     *Initialize the dynamic array of struct sensor_t and it's length is equal to no of line read from file i.e. line_counters
     */
    sensor = (struct sensor_t *) malloc(line_counter * sizeof(struct sensor_t));

    /**
     * @param fptr
     * @param sensor
     * @return
     * <p>This function parse the csv file</p>
     */
    result = parseFile(fptr, sensor);
    /*
     * If function returns 1 then the file is parse successfully.
     */
    if (result == 1)
        printf("success\n");
    else
        printf("failure\n");

    /*
     * print the parse data
     */
    for (int i = 0; i < line_counter; i++) {
        printf("The time is %s ", (sensor + i)->time);
        printf("The name is %s ", (sensor + i)->name);
        printf("The data is %lf ", (sensor + i)->data);
        printf("\n");
    }

    return 0;
}