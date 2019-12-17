#include <CUnit/Basic.h>
#include <stdlib.h>
#include <time_structure.h>
#include <sensor_structure.h>
#include <validate_sensor.h>
#include <unique_time.h>
#include <input_output_csv.h>
#include <support_degree_matrix.h>
#include <eigen.h>
#include <principal_component.h>
#include <contribution_rate_k_component.h>
#include <contribution_rate_m_component.h>
#include <eliminate_incorrect_data.h>
#include <weight_coefficient_sensor.h>
#include <integrated_support_score.h>
#include <sensor_fusion_algorithm.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

void test_run_validate(void);
void test_run_unique_time(void);
void test_run_support_degree_matrix(void);
void test_run_stuck_sensor(void);
void test_run_sensor_fusion(void);
void test_run_input_output(void);
void test_run_eigen(void);
void test_run_principal_component(void);
void test_run_contribution_rate_k_component(void);
void test_run_contribution_rate_m_component(void);
void test_run_integrated_support_score(void);
void test_run_eliminate_incorrect_data(void);
void test_run_weight_coefficient_sensor(void);
void test_run_sensor_fusion_algorithm(void);

int init_suite(void) {
    return 0;
}
int clean_suite(void) {
    return 0;
}
void test_run_input_output(void){
    FILE *p_fptr;
    sensor_t *p_sensor;
    char line[1024];
    /**
     * The proper file name and path is provided to the fopen function and successfully read all the values of the provided csv file and return 1.
     * The assert function compare the actual output(1) with expected output(1) and pass the test case.
     * */
    p_fptr = fopen("data/sample.csv", "r");
    int line_counter=0;
    while (fgets(line, 1024, p_fptr)) {
        line_counter++;
    }
    p_sensor = (sensor_t *) malloc(line_counter * sizeof(sensor_t));
    CU_ASSERT_EQUAL(1,read_csv(p_fptr, p_sensor));
    /**
     *The wrong file name is provided to the fopen function so the pointer to the file would be null and return -1.
     * The assert function compare the actual output(-1) with expected output(-1) and pass the test case.
    */
    p_fptr = fopen("data/samfsple.csv", "r");
    CU_ASSERT_EQUAL(-1,read_csv(p_fptr, p_sensor));
    free(p_fptr);
    free(p_sensor);
}
void test_run_validate(void){
    sensor_t *p_sensor,*v_sensor;
    p_sensor = (sensor_t *) malloc(2* sizeof(sensor_t));
    v_sensor = (sensor_t *) malloc(2 * sizeof(sensor_t));
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53;
    double min=50;
    double max=55;
    int line_counter=1;
    time_tt time;
    time.tm_hour=1;
    time.tm_min=20;
    CU_ASSERT_EQUAL(1, compare_sensor_range(p_sensor,min,max,line_counter,time,v_sensor));
    p_sensor++;
    v_sensor++;
    strcpy(p_sensor->time,"1:30");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=20;
    time_tt time1;
    time1.tm_hour=1;
    time1.tm_min=30;
    CU_ASSERT_EQUAL(0, compare_sensor_range(p_sensor,min,max,line_counter,time1,v_sensor));
    free(p_sensor);
    free(v_sensor);
}
void test_run_unique_time(void){
    time_tt time1,time2;
    time1.tm_hour=1;
    time1.tm_min=30;
    char *time="1:30";
    time2=time_parse(time,time1 );
    int x=time2.tm_hour;
    int y=time2.tm_min;
    CU_ASSERT(x==time1.tm_hour && y==time1.tm_min);
    sensor_t *p_sensor;
    p_sensor = (sensor_t *) malloc(1* sizeof(sensor_t));
    int line_counter=1;
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53;
    CU_ASSERT_EQUAL(1,get_uniquetime_length(p_sensor,line_counter));
    int length_time_list=1;
    time_tt *time3;
    time3=get_time_list(p_sensor,line_counter,length_time_list);
    CU_ASSERT(1== time3[0].tm_hour && 20==time3[0].tm_min);

}
void test_run_support_degree_matrix(void)
{
    sensor_t *p_sensor;
    p_sensor = (sensor_t *) malloc(2* sizeof(sensor_t));
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor1");
    p_sensor->data=53.6;
    p_sensor++;
    strcpy(p_sensor->time,"1:20");
    strcpy(p_sensor->name,"sensor2");
    p_sensor->data=52.7;
    p_sensor --;

    double **pp_D_array_a,**pp_D_array_e;
    int no_sensor=2;
    pp_D_array_a=(double **)malloc(sizeof(double *) * no_sensor);

    for(int rows=0;rows<no_sensor;rows++){
        pp_D_array_a[rows]= (double *)malloc(sizeof(double) * no_sensor);
    }
    pp_D_array_a[0][0]=1.000000;
    pp_D_array_a[0][1]=0.406570;
    pp_D_array_a[1][0]=0.406570;
    pp_D_array_a[1][1]=1.000000;

    pp_D_array_e = compute_support_degree_matrix(p_sensor,no_sensor);
    for(int rows=0;rows<2;rows++){
        for(int cols=0;cols<2;cols++)
        {
            //printf("%lf\n",pp_D_array_a[rows][cols]);
            //printf("%lf\n",pp_D_array_e[rows][cols]);

            CU_ASSERT(fabs(pp_D_array_a[rows][cols]-pp_D_array_e[rows][cols])<0.001);
        }

    }
    free(p_sensor);
    free(pp_D_array_a);
    free(pp_D_array_e);

}
void test_run_eigen(void)
{

    double **pp_D_array;
    int no_sensor=2;
    pp_D_array=(double **)malloc(sizeof(double *) * no_sensor);

    for(int rows=0;rows<no_sensor;rows++){
        pp_D_array[rows]= (double *)malloc(sizeof(double) * no_sensor);
    }
    pp_D_array[0][0]=1.000000;
    pp_D_array[0][1]=0.406570;
    pp_D_array[1][0]=0.406570;
    pp_D_array[1][1]=1.000000;
    double *p_eigen_val;
    double **pp_eigen_vector;

    p_eigen_val=(double *)malloc(sizeof(double) * no_sensor);

    pp_eigen_vector=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_eigen_vector[i]=(double *) malloc(sizeof(double) * no_sensor);
    }
    CU_ASSERT_EQUAL(1,compute_eigen(pp_D_array,no_sensor,p_eigen_val,pp_eigen_vector));
    free(pp_eigen_vector);
    free(pp_D_array);
    free(p_eigen_val);
}
void test_run_principal_component(void)
{
    double **pp_eigen_vector,**pp_D_array;
    int no_sensor = 2;
    pp_eigen_vector=(double **)malloc(sizeof(double *) * no_sensor);
    pp_D_array=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_eigen_vector[i]=(double *) malloc(sizeof(double) * no_sensor);

    }
    pp_D_array=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++) {
        pp_D_array[i] = (double *) malloc(sizeof(double) * no_sensor);
    }
    double **pp_principal_component_a,**pp_principal_component_e;
    pp_principal_component_a=(double **)malloc(sizeof(double *) *no_sensor);
    for(int i=0;i<no_sensor;i++) {
        pp_principal_component_a[i] = (double *) malloc(sizeof(double) * no_sensor);
    }
    pp_D_array[0][0]=1.000000;
    pp_D_array[0][1]=0.406570;
    pp_D_array[1][0]=0.406570;
    pp_D_array[1][1]=1.000000;
    pp_eigen_vector[0][0]=1.000000;
    pp_eigen_vector[0][1]=2.000000;
    pp_eigen_vector[1][0]=1.000000;
    pp_eigen_vector[1][1]=2.000000;
    pp_principal_component_a[0][0]=1.813140;
    pp_principal_component_a[0][1]=2.406570;
    pp_principal_component_a[1][0]=1.813140;
    pp_principal_component_a[1][1]=2.406570;
    pp_principal_component_e=compute_principal_component(pp_eigen_vector,pp_D_array,no_sensor);
    for(int i=0;i<no_sensor;i++) {
        for(int j=0;j<no_sensor;j++) {
            printf("%lf %lf",pp_principal_component_e[i][j],pp_principal_component_a[i][j]);
            CU_ASSERT(fabs(pp_principal_component_e[i][j]-pp_principal_component_a[i][j])<0.01);
        }
    }

}
void test_run_contribution_rate_k_component(void)
{

    int no_sensor = 3;
    double *p_alpha_a,*p_alpha_e,*p_eigen_val;
    p_eigen_val=(double *)malloc(sizeof(double) * no_sensor);
    p_alpha_a=(double *)malloc(sizeof(double) * no_sensor);
    p_eigen_val[0]=1.0;
    p_eigen_val[1]=2.0;
    p_eigen_val[2]=3.0;
    p_alpha_a[0]=0.166667;
    p_alpha_a[1]=0.333334;
    p_alpha_a[2]=0.500000;
    p_alpha_e=compute_contribution_K_rate(p_eigen_val,no_sensor);
    for(int i=0;i<no_sensor;i++){
        //printf("%lf",p_alpha_a[i]);
        //printf("%lf",p_alpha_e[i]);
        CU_ASSERT(fabs(p_alpha_a[i]-p_alpha_e[i])<0.001);
    }
    free(p_alpha_a);
    free(p_alpha_e);
    free(p_eigen_val);

}
void test_run_contribution_rate_m_component(void)
{
    int no_sensor=3;
    double *p_alpha;
    p_alpha=(double *)malloc(sizeof(double) * no_sensor);
    p_alpha[0]=0.166667;
    p_alpha[1]=0.333334;
    p_alpha[2]=0.500000;
    double thresold=0.5;
    int new_no_sensor_a = 2;
    int new_no_sensor_e = compute_contribution_M_rate(p_alpha,no_sensor,thresold);
    CU_ASSERT_EQUAL(new_no_sensor_a,new_no_sensor_e);

}
void test_run_integrated_support_score(void)
{
    int no_sensor=3;
    int new_no_sensor=2;
    double *p_alpha;
    double **pp_y_value;
    p_alpha=(double *)malloc(sizeof(double) * no_sensor);
    pp_y_value=(double **)malloc(sizeof(double *) * no_sensor);
    for(int i=0;i<no_sensor;i++){
        pp_y_value[i]=(double *) malloc(sizeof(double) * no_sensor);
    }
    p_alpha[0]=1;
    p_alpha[1]=2;
    p_alpha[2]=3;
    pp_y_value[0][0]=1;
    pp_y_value[0][1]=2;
    pp_y_value[0][2]=3;
    pp_y_value[1][0]=4;
    pp_y_value[1][1]=5;
    pp_y_value[1][2]=6;
    pp_y_value[2][0]=7;
    pp_y_value[2][1]=8;
    pp_y_value[2][2]=9;
    double *p_Z_e,*p_Z_a;
    p_Z_e=(double *)malloc(sizeof(double) * no_sensor);
    p_Z_e[0]=9.000000;
    p_Z_e[1]=12.000000;
    p_Z_e[2]=15.000000;
    p_Z_a = compute_integrated_score(p_alpha,pp_y_value ,no_sensor,new_no_sensor);
    for(int i=0;i<no_sensor;i++){
        CU_ASSERT(fabs(p_Z_e[i]-p_Z_a[i])<0.001);
    }

}

void test_run_eliminate_incorrect_data(void)
{
    double *p_Z;
    int no_sensor=3;
    p_Z=(double *)malloc(sizeof(double) * no_sensor);
    double fault_value=0.7;

    p_Z[0]=5.0;
    p_Z[1]=10.0;
    p_Z[2]=15.0;

    int *p_discard_index_a,*p_discard_index_e;
    p_discard_index_a=(int*)malloc(sizeof(int) * no_sensor);
    p_discard_index_a[0]=1;
    p_discard_index_a[1]=0;
    p_discard_index_a[2]=0;
    p_discard_index_e=eliminate_data(p_Z,fault_value,no_sensor);
    for(int i=0;i<no_sensor;i++){
        //printf("%d",p_discard_index_e[i]);
        CU_ASSERT_EQUAL(p_discard_index_a[i],p_discard_index_e[i]);
    }

}
void test_run_weight_coefficient_sensor(void)
{

}
void test_run_sensor_fusion_algorithm(void)
{

}

int main (void)// Main function
{
    CU_pSuite pSuite = NULL;

    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add suite1 to registry
    pSuite = CU_add_suite("Main_Test_Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // add test1 to suite1
    if ((NULL == CU_add_test(pSuite, "test_input_output", test_run_input_output)) ||
        (NULL == CU_add_test(pSuite, "test_unique_time", test_run_unique_time))
        ||
        (NULL == CU_add_test(pSuite, "test_validate_sensor", test_run_validate)) ||
        (NULL == CU_add_test(pSuite, "test_Support_Degree", test_run_support_degree_matrix))
        || (NULL == CU_add_test(pSuite, "test_contribution_rate_k_component", test_run_contribution_rate_k_component))
        || (NULL == CU_add_test(pSuite, "test_contribution_rate_m_component", test_run_contribution_rate_m_component))
        || (NULL == CU_add_test(pSuite, "test_eliminate_incorrect_data", test_run_eliminate_incorrect_data))
        || (NULL == CU_add_test(pSuite, "test_eigen", test_run_eigen))
        || (NULL == CU_add_test(pSuite, "test_principal_component", test_run_principal_component))
        || (NULL == CU_add_test(pSuite, "test_integrated_support_score", test_run_integrated_support_score)))
        //(NULL == CU_add_test(pSuite, "test_sensor_fusion",test_run_sensor_fusion))
        //||
        //(NULL == CU_add_test(pSuite, "test_stuck_sensor",test_run_stuck_sensor)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();// OUTPUT to the screen
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    CU_cleanup_registry();//Cleaning the Registry
    return CU_get_error();
}