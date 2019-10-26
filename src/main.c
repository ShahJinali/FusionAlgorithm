#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parse_csv_file.h>

/**
 * @author:Jinali SHah
 * @version:1.0
 * @date : 2019/10/25
 * @return
 */
int main() {
    char ** sensor_name;
    char ** sensor_time;
    double * sensor_data;
    FILE * fptr;
    char line[1024];
    int loop_counter=0;
    int result_ParseCSVFile;
    /*
     * Initialize file pointer
     */
    fptr=fopen("../sample.csv","r");
    if(fptr == NULL){
        printf("File pointer is not initialized");
        return -1;
    }

    /*
     * Read the line to get the no of line and initialize the dynamic array for sensor_name,sensor_time,sensor_data
     */
    while(fgets(line,1024,fptr)){
        loop_counter++;
    }
    printf("The total no of lines is %d\n", loop_counter);

    /*
     * Set the pointer to the beginning of file
     */
    fseek(fptr,0,0);
    /*
     * Initialize the sensor_data,sensor_time,sensor_name dynamic array
     * The size of array is equal to the length of line read from file
     */
    sensor_data=(double *)malloc(loop_counter * sizeof(double));
    sensor_name=(char **) malloc(loop_counter * sizeof(char));
    sensor_time=(char **)malloc(loop_counter * sizeof(char));

    /*
     * call the parseFile method and pass the parameter
     */
    result_ParseCSVFile=parseFile(fptr,sensor_time,sensor_name,sensor_data);

    if(result_ParseCSVFile == 1)
        printf("Success\n");
    else
        printf("Failure\n");

    /*
     * Printing the data obtained after parsing file
     */
    for(int i=0;i<loop_counter;i++){
        printf(" %s %s %lf \n",sensor_time[i],sensor_name[i],sensor_data[i]);
    }
    return 0;
}