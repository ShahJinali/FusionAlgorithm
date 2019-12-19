#include <CUnit/Basic.h>

int init_suite(void) {
    return 0;
}
int clean_suite(void) {
    return 0;
}
void test_run_input_output(){

}
int main (void)// Main function
{
    CU_pSuite pSuite=NULL;

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
    if ( (NULL == CU_add_test(pSuite, "test_input_output",test_run_input_output))
//            (NULL == CU_add_test(pSuite, "test_unique_time",test_run_unique_time)) ||
//            (NULL == CU_add_test(pSuite, "test_validate_sensor",test_run_validate)) ||
//            (NULL == CU_add_test(pSuite, "test_sensor_fusion",test_run_sensor_fusion)) ||
//            (NULL == CU_add_test(pSuite, "test_stuck_sensor",test_run_stuck_sensor))
            )
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