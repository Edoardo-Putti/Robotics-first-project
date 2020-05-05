920884 Belotti Leonardo
928148 Boiano Antonio
948644 Putti Edoardo

------------------------------------
first_project/cfg/parameters.cfg:
Configuration file to setup the dynamic reconfigure of the system.

first_project/msg/custom.msg:
Custom message needed to publish the computed distance and the status flag.

first_project/msg/DistanceCalculator.srv:
Service parameter definition.

first_project/src/pub.cpp:
Source file of the node responsible of converting the data read from the bag from GPS to ENU
and publish it. Moreover it publish the odometry and the tf.

first_project/src/collector.cpp:
Source file of the node responsible of collecting and synchronize the ENU positions
of the car and the obstacle, ask for the service the distance and publish the custom message
with the computed distance and the flag.

first_project/src/distance_calc.cpp:
Source file of the node server responsible of computing the distance between 2 ENU positions.


first_project/launch/launcher.launch:
Launch file will automatically play the given bag inside the launch folder,
run two instances of the node defined in sub.cpp using two different frames one
for the car and one for the obstacle, moreover it starts the collector node and the service.
In the Launch file are also defined some initial parameters:

latitude_init, longitude_init, and h0 which represent respectively the latitude initial position, the longitude initial position, and the altitude initial positions used for the ENU computation, and set by default as the Car starting point.

A safe and unsafe parameter which represents the inital value of the lower bound for the safe distance, and the lower bound for the unsafe distance.

----------------------------------------
How to Use DYNAMIC RECONFIGURE:
Dynamic reconfigure starts automatically thanks to the launch file.
the parameter "safe" is the lower bound for the safe distance that goes from 5 to 100,
with the default value equal to 5
the parameter "unsafe" is the lower bound for the unsafe distance that goes from 1 to 5,
with the default value equal to 1.

------------------------------------------
TF-TREE
see the tf_tree.png image
------------------------------------------

CUSTOM MESSAGES' STRUCTURE
first_project/msg/custom.msg 
float64 distance
string flag

--------------------------------------------
copy the folder first_project in the src folder of your ROS workspace then source your terminal and compile:
$ source devel/setup.bash
$ catkin_make

launch the launch file:
$ roslaunch first_project launcher.launch
roscore,the bag and the nodes will start immediately;
the rqt_reconfigure will start automatically in few seconds;



use dynamic reconfigure to set the parameters

to visualize the system's trajectory start rviz and leave the fixed frame to "map" and add the tf or the odometry; 

----------------------------------------------
