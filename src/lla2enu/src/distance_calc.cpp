#include "ros/ros.h"
#include <string.h>
#include "lla2enu/DistanceCalculator.h"


bool distance(lla2enu::DistanceCalculator::Request  &req,
 lla2enu::DistanceCalculator::Response &res){


  float x1=req.x;
  float y1=req.y;
  float z1=req.z;
  float x2=req.x_obs;
  float y2=req.y_obs;
  float z2=req.z_obs;

  ROS_INFO(" Ready to calculate the distance between the two objects");

  float ans = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2) );


  res.distance=ans;

  ROS_INFO("the distance is: %f",res.distance);

  
  return true; 



}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "distance_calc_server");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("distance_calc", distance);
  ros::spin();

  return 0;
}
