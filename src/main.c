#include <stdio.h>
#include <stdlib.h>
#include <parse_csv_file.h>

/**
 * @author : Jinali Shah
 * @version:1.2
 * @date :2019/10/27
 * @return
 */
//create the pointer of structure whose size is equal to no of lines in .csv file
int main() {

    struct sensor_t *sensor;
    FILE *fptr;
    char line[1024];
    int line_counter = 0;
    int result;
    fptr = fopen("../sample.csv", "r");

    //read line and increment counter for each line read
    while (fgets(line, 1024, fptr)) {
        line_counter++;
    }

    //set the cursor to the beginning of file
    fseek(fptr, 0, 0);

    //initialize the dynamic array of  structure sensor_t  sensor
    sensor = (struct sensor_t *) malloc(line_counter * sizeof(struct sensor_t));

    //call the parseFile function
    result = parseFile(fptr, sensor);
    if (result == 1)
        printf("success");
    else
        printf("failure");

    //print the parse data
    for (int i = 0; i < line_counter; i++) {
        printf("The time is %s ", (sensor + i)->time);
        printf("The name is %s ", (sensor + i)->name);
        printf("The data is %lf ", (sensor + i)->data);
        printf("\n");
    }
    printf("Hello, World!\n");
    return 0;
}