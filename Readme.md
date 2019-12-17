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
Our Project will follow the conventional C file structure.<br>
SensorFusion<br>
│  README.md<br>
│   INSTALL.md<br>
|   .gitignore<br>
|   makefile<br>
|<br>
└───src<br>
|   &nbsp;&nbsp;&nbsp;&nbsp;|   contribution_rate_k_component.c<br>
|   |   contribution_rate_m_component.c<br>
|   |   eigen.c<br>
|   |   eliminate_incorrect_data.c<br>
|   |   input_output_csv.c<br>
|   |   integrated_support_score.c<br>
|   |	main.c<br>
|	|	principal_component.c<br>
|	|	sensor_fusion_algorithm.c<br>
|	|	stuck_sensor.c<br>
|	|	support_degree_matrix.c<br>
|	|	unique_time.c<br>
|	|	validate_sensor.c<br>
|	|	weight_coefficient_sensor.c<br>
|<br>
└───include<br>
|   |   contribution_rate_k_component.h<br>
|   |   contribution_rate_m_component.h<br>
|   |   eigen.h<br>
|   |   eliminate_incorrect_data.h<br>
|   |   input_output_csv.h<br>
|   |   integrated_support_score.h<br>
|	|	principal_component.h<br>
|	|	sensor_fusion_algorithm.h<br>
|	|	sesnor_structure.h<br>
|	|	stuck_sensor.h<br>
|	|	support_degree_matrix.h<br>
|	|	time_structure.h<br>
|	|	unique_time.h<br>
|	|	validate_sensor.h<br>
|	|	weight_coefficient_sensor.h<br>
|<br>
└───data<br>
|   |   sample.csv<br>
|<br>
└───test<br>
|	└───src<br>
|	|	|	testMain.c<br>
|<br>
└───doc<br>
│   └───html<br>
|   |   |	index.html<br>
|	|	|	...<br>


# Install
To install the dependencies and run this software , refer to INSTALL.md file

# Documentation
To see the user level documentation ,refer to doc/ folder

# Aknowledgement
> -Dr. Cristina Ruiz Martin for providing advice on how to develop the software.

# Support
If you face any problem while installing the libraries, compiling and running the program.
Please feel free to contact on the email address specified in author section.