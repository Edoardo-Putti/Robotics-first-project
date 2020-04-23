#include "ros/ros.h"
#include "lla2enu/DistanceCalculator.h"


bool dist(lla2enu::DistanceCalculator::Request  &req,
         lla2enu::DistanceCalculator::Response &res){

    float toRadians = 0.0174533;
    float R = 6371;     // Radius of Earth in Kilometers, R = 6371 

    float lat1=req.x;
    float long1=req.y;
    float lat2=req.x_obs;
    float long2=req.y_obs;

ROS_INFO(" Pronto per calcolare Input x: %f y: %f x_obs: %f y_obs: %f",req.x,req.y,req.x_obs,req.y_obs );

    lat1 = toRadians*lat1; 
    long1 = toRadians*long1; 
    lat2 = toRadians*lat2; 
    long2 = toRadians*long2; 

    // Haversine Formula 

    float dlong = long2 - long1; 
    float dlat = lat2 - lat1; 
    float ans = pow(sin(dlat / 2), 2)+cos(lat1)*cos(lat2)*pow(sin(dlong / 2), 2); 

    ans = (2 * asin(sqrt(ans)))*R; 

    res.distance=ans;

    ROS_INFO("Ho calcolato la distanza: %f",res.distance);
     
    return true; 

//Introdurre altezza z per la distanza

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "distance_calc_server");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("distance_calc", dist);
  ROS_INFO("Ready to compute the distance");
  ros::spin();

  return 0;
}
