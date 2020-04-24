#include "ros/ros.h"
#include <string.h>
#include "lla2enu/DistanceCalculator.h"


bool distanza(lla2enu::DistanceCalculator::Request  &req,
         lla2enu::DistanceCalculator::Response &res){


    float x1=req.x;
    float y1=req.y;
    float z1=req.z;
    float x2=req.x_obs;
    float y2=req.y_obs;
    float z2=req.z_obs;

ROS_INFO(" Pronto per calcolare Input x: %f y: %f x_obs: %f y_obs: %f",req.x,req.y,req.x_obs,req.y_obs );

    float ans = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2) );

    if(ans > 5){
	res.flag = "Safe";
	}
    else if(ans > 1 && ans <= 5){
	res.flag = "Unsafe";
	}
    else{
	res.flag = "Crash";
	}
    res.distance=ans;

    ROS_INFO("Ho calcolato la distanza: %f",res.distance);
    ROS_INFO("Ho settato la flag: %s",res.flag.c_str());
     
    return true; 

//Introdurre altezza z per la distanza

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "distance_calc_server");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("distance_calc", distanza);
  ROS_INFO("Ready to compute the distance");
  ros::spin();

  return 0;
}
