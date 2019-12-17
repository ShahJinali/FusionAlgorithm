# Assumption

## Consider the following assumption when passing input **.csv** file to the program

* The default data is available under **data/sample.csv**.

* The user must sepcify the **comma separated value** only.

* User can specify their own input .csv file as well.

* The order of column in input .csv must be in form of **<sensor_name>,<sensor_time>,<sensor_data>**.

* The order of column should not be changed.

* The sensor_name should be consistent and number of sensors in each time slot is assumed to be same.
	> For instance, at time 1:20 ,there is sensor1,sensor2 and sensor3.
	> Then, at time 1:50 there should be same sensor name i.e. sensor1,sensor2 and sensor3 and same number of sensor.

* The input .csv should be sorted in context of time and sensor name.

* The sensor_time is in **24clock** format specified in hours and mins.

* Algorithm doesn't consider the next day.So, the time should be in ascending form i.e.( 00:00,1:00, 2:00, 13:10,...,23:59).


# Compile and Run

**Before building and running the software , read the INSTALL.md file for installing the dependencies.**

## Building the Project

* Download the project on your device.

* Extract the zip folder.

* Open the command prompt and redirect to the path of project.

	>  Type the following commands to build the project.<br>
		>> make clean<br>
		>> make<br>

## Run the project

* Tu run the project , build the project first.

* Open the command prompt and redirect to the path of project.

	>  Type the following commands to build the project.
		>> cd bin<br>
		>> FusedOuput <input-file-path> <minimum-value> <maximum-value><br>

	> For instance , run as **FusedOuput ../data/sample.csv 50 55**