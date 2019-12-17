# About
The user performs the readings with a set of set of sensors, but there will be error associated with the measurment.
So, the user is interested in generating more accuarate outcome.Thus, we have implemented a fusion algorithm using the principal component analysis.
This fusion algorithm takes the input from .csv file and generate the fused output.Before, performing fusion algorithm it checks the validity of sensor.
The user provides the minimum and maximum range of sensor to validate the sensors. Only the validated sensor data is passed to fusion algorithm.
It also computes the sensor which are stuck. The sensors are said to be stuck if its value doesn't change after given time interval.

Below is the paper which describes the steps and results of fusion algorithm.<br>
G. Hongyan, “A simple multi-sensor data fusion algorithm based on principal component analysis,” in 2009 ISECS International Colloquium on Computing, Communication, Control, and Management, Sanya, China, 2009, pp. 423–426.

# Author
> - Shah Jinaliben <jinalibenhiteshbhais@cmail.carleton.ca> -Univeristy of Ottawa
> - Shah Rushabh <RushabhSudhirkumarSh@cmail.carleton.ca> -Univeristy of Ottawa
> - Patel Jay <jpate122@uottawa.ca> -Univeristy of Ottawa

# Project Folder Structure
Our Project will follow the conventional C file structure.
SensorFusion
│  README.md<br>
│   INSTALL.md<br>
|   .gitignore
|   makefile
|
└───src
|   |   contribution_rate_k_component.c
|   |   contribution_rate_m_component.c
|   |   eigen.c
|   |   eliminate_incorrect_data.c
|   |   input_output_csv.c
|   |   integrated_support_score.c
|   |	main.c
|	|	principal_component.c
|	|	sensor_fusion_algorithm.c
|	|	stuck_sensor.c
|	|	support_degree_matrix.c
|	|	unique_time.c
|	|	validate_sensor.c
|	|	weight_coefficient_sensor.c
|
└───include
|   |   contribution_rate_k_component.h
|   |   contribution_rate_m_component.h
|   |   eigen.h
|   |   eliminate_incorrect_data.h
|   |   input_output_csv.h
|   |   integrated_support_score.h
|	|	principal_component.h
|	|	sensor_fusion_algorithm.h
|	|	sesnor_structure.h
|	|	stuck_sensor.h
|	|	support_degree_matrix.h
|	|	time_structure.h
|	|	unique_time.h
|	|	validate_sensor.h
|	|	weight_coefficient_sensor.h
|
└───data
|   |   sample.csv
|
└───test
|	└───src
|	|	|	testMain.c
|
└───doc
│   └───html
|   |   |	index.html
|	|	|	...


# Install
To install the dependencies and run this software , refer to INSTALL.md file

# Documentation
To see the user level documentation ,refer to doc/ folder

# Aknowledgement
> -Dr. Cristina Ruiz Martin for providing advice on how to develop the software.

# Support
If you face any problem while installing the libraries, compiling and running the program.
Please feel free to contact on the email address specified in author section.