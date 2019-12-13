#include <stdio.h>
#include <stdlib.h>
#include <input_output_csv.h>
#include <sensor_fusion_algorithm.h>
#include <stuck_sensor.h>
#include <string.h>
#include <time_structure.h>
#include <unique_time.h>
#include <validate_sensor.h>

void str_error();
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
/*
 * argc holds the no of arguments passed.By default, the argument length == 1 which contains the name of the program
 * Thus argv[0] holds the program name.
 * Order of Arguments to be passed are "name of .csv file, sensor min range,sensor max range,
 * time interval,parameter p of algorithm, parameter q of algorithm"
 */
int main(int argc,char *argv[]) {

    char *name_file;
    int sensor_min_range;
    int sensor_max_range;
    /*
     * Default value If not specified by user
     */
    time_tt interval;
    interval.tm_hour=0;
    interval.tm_min=10;
    double q_fault=0.7;
    double p=0.85;

    FILE *p_fptr;
    char line[1024];
    int loop_counter=0;
    int result;
    sensor_t *p_sensor;
    char **unique_time;
    char path_prefix[9]="../data/";
    char *file_path;

    if(argc >=1 && argc < 4){
        str_error();
        return -1;
    }
    else{
        /*
        Assuming the argv[1] is the name of file
         */
        name_file=argv[1];
        file_path=strcat(path_prefix,name_file);
        /*
         Assuming the argv[3] is min range and argv[4] is max range
         */
        sensor_min_range=atoi(argv[2]);
        sensor_max_range=atoi(argv[3]);
        /*
         argv[5] , argv[6] and argv[7] is optional ,so If user doesn't specify then it will take the default value.
         */
        if(argc == 5) {
            interval = time_parse(argv[4], interval);
        }
        else if (argc == 6) {
            interval = time_parse(argv[4], interval);
            q_fault = atof(argv[5]);
        }
        else if (argc == 7) {
            interval = time_parse(argv[4], interval);
            q_fault = atof(argv[5]);
            p = atof(argv[6]);
        }

        printf("%s\n",name_file);
        printf("%s\n",file_path);
        printf("%d\n",sensor_min_range);
        printf("%d\n",sensor_max_range);
        printf("%d %d\n",interval.tm_hour,interval.tm_min);
        printf("%lf \n",q_fault);
        printf("%lf \n",p);
    }
    /**
        This is the pointer to file sample.csv.The file sample.csv is open in read mode
     */
    p_fptr = fopen(file_path, "r");

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
        loop_counter++;
    }
    const int line_counter=loop_counter;

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

   /*
    * Get the length of unique time
    */
   int length_unique_time=get_uniquetime_length(p_sensor,line_counter);
   printf("The length of time list is %d\n",length_unique_time);
   /*
    Call get_time_list
    */
    time_tt *p_time_list =  get_time_list(p_sensor,line_counter,length_unique_time);

    /*
     * Call the validate sensor and fusion algorithm
     */
    int sensor_len;
    sensor_t *p_v_sensor;
    for(int i=0;i<length_unique_time;i++){
        p_v_sensor=(sensor_t *)malloc(sizeof(sensor_t) * (line_counter/length_unique_time));
        sensor_len=compare_sensor_range(p_sensor,sensor_min_range,sensor_max_range,line_counter,p_time_list[i],p_v_sensor);
        /*
         * All the sensors are out of range
         */
        if(sensor_len == 0){
            printf("ALL THE SENSORS ARE OUT OF RANGE\n");
        }
        else if(sensor_len == 1){
            printf("The Fused output IS %lf\n",(p_v_sensor+0)->data);
        }else{
            sensor_fusion(p_v_sensor,sensor_len);
        }
        free(p_v_sensor);
    }

    /*
     * Call the stuck sensor algorithm
     */
    compute_stuck_sensor(p_sensor,p_time_list,interval,length_unique_time,line_counter);

    /*
     * Free the Memory
     */
    free(p_fptr);
    free(p_sensor);
    free(p_time_list);
    return 0;
}

void str_error(){
    printf("Insufficient no of arguments\n");
    printf("Provide the arguments in this format");
    printf("Order of Arguments to be passed are :name of .csv file,no of sensor in each grp, sensor min range,sensor max range,\n"
           "time interval,parameter p of algorithm, parameter q of algorithm");
}
