#include <stdio.h>
#include <stdlib.h>
#include <input_output_csv.h>
#include <sensor_fusion_algorithm.h>
#include <unique_value.h>
/**
 * @author : Jinali Shah
 * @version:1.1
 * @date :2019/10/27
 * @return
 *  <p>This is main function and executable file will run this function</p>
 */
/*
 * Declare as global variable in main.c and initialize here and it is used as extern int line_counter in other files
 */
int line_counter;
int main() {

    sensor_t *p_sensor;
    char **unique_time;
    /**
        This is the pointer to file sample.csv.The file sample.csv is open in read mode
     */
    FILE *p_fptr;
    char line[1024];
    line_counter = 0;
    int result;
    p_fptr = fopen("../sample.csv", "r");

    /**
     * If file is not found in specified path ,then it will return -1 and exit the program
     */
    if (p_fptr == NULL) {
        printf("The file pointer is not initialize");
        return -1;
    }
    /*
    * This loop is used to read the number of lines of file.So it can be further used to initialize the dynamic
     * array of sensor_t *p_sensor
    */
    while (fgets(line, 1024, p_fptr)) {
        line_counter++;
    }

    /*
     * Set the cursor at the beginning of file
     */
    fseek(p_fptr, 0, 0);

    /*
     *Initialize the dynamic array of sensor_t and it's length is equal to no of line read from file i.e. line_counters
     */
    p_sensor = (sensor_t *) malloc(line_counter * sizeof(sensor_t));

    /**
     * @param p_fptr
     * @param p_sensor
     * @return
     * <p>This function parse the csv file</p>
     */
    result = read_csv(p_fptr, p_sensor);
    /*
     * If function returns 1 then the file is parse successfully.
     */
    if (result == 1)
        printf("success\n");
    else
        printf("failure\n");

   printf("Line Counter%d\n",line_counter);

    //call sensor fusion algorithm
    sensor_fusion(p_sensor,line_counter);

//    //get the unique value of time and store it in unique_time char array
//    unique_time=struniquetime(p_sensor);
//    //get the no of unique value
//    int length_unique_time=struniquelen(p_sensor);
//
//    /*
//     * Print the length of unique_time and data of unique_time
//     */
//    printf("%d\n",length_unique_time);
//    for(int i=0;i<length_unique_time;i++){
//        printf("%s\n",unique_time[i]);
//    }
    return 0;
}