cmake_minimum_required(VERSION 2.8.3)
project(lla2enu)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs geodesy sensor_msgs tf nav_msgs geometry_msgs)






## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime geometry_msgs)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})



add_executable(enu_front src/sub.cpp)
add_dependencies(enu_front ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(enu_front ${catkin_LIBRARIES})


add_executable(enu_obs src/subobs.cpp)
add_dependencies(enu_obs ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(enu_obs ${catkin_LIBRARIES})

