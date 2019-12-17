$(shell mkdir -p bin)
$(shell mkdir -p build)
CC =gcc
CFLAGS =-g -Wall
INCLUDES=-I"include" -I"C:\cygwin64\usr\include"
LFLAGS=-LC:\cygwin64\lib
LIBS=-lgsl -lgslcblas -lm
TARGET=FusedOutput

default :$(TARGET)

$(TARGET): main.o eigen.o contribution_rate_k_component.o contribution_rate_m_component.o eliminate_incorrect_data.o input_output_csv.o integrated_support_score.o unique_time.o principal_component.o sensor_fusion_algorithm.o support_degree_matrix.o weight_coefficient_sensor.o validate_sensor.o stuck_sensor.o
	$(CC) $(CFLAGS) $(LFLAGS) -o bin/$(TARGET) build/main.o build/eigen.o build/contribution_rate_k_component.o build/unique_time.o build/contribution_rate_m_component.o build/eliminate_incorrect_data.o build/input_output_csv.o build/integrated_support_score.o build/principal_component.o build/sensor_fusion_algorithm.o build/support_degree_matrix.o build/weight_coefficient_sensor.o build/validate_sensor.o build/stuck_sensor.o $(LIBS)

%.o : src/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $^ -o build/$@

#CLEAN COMMANDS
clean:
	rm -f bin/* build/*