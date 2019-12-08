#include <stdio.h>
#include <stdlib.h>

int compute_contribution_M_rate(double *p_alpha_value,int no_sensor,double p){

    int m;
    double *p_m_rate;
    p_m_rate=(double *)malloc(sizeof(double) * no_sensor);

    /*
     * Step1 compute all p_m_rate value
     */
    for(int i=0;i<no_sensor;i++){
        double sum=0.0;
        for(int j=0;j<=i;j++){
            sum=sum+p_alpha_value[j];
        }
        p_m_rate[i]=sum;
    }

    //return only first p_m_rate value such p_m_rate >p
    for(int i=0;i<no_sensor;i++){
        if(p_m_rate[i] > p){
            m=i+1;
            break;
        }
    }
    free(p_m_rate);
    return m;
}
