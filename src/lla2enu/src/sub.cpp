#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include "sensor_msgs/NavSatFix.h"
#include <math.h>
#include "geometry_msgs/Vector3Stamped.h"
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#define scale_factor 100

class pub_sub_car
{

private:
  ros::NodeHandle n;  
  ros::Subscriber sub;
  ros::Publisher pub;

 nav_msgs::Odometry odom;
 ros::Publisher pub_odom;

 

  tf::Transform transform;
  tf::TransformBroadcaster br;

//Global Variables

  geometry_msgs::Vector3Stamped p;
  std::string bag_pos;
  std::string name_space;
  float latitude_init;
  float longitude_init;
  float h0;
//int conta;

public:
 pub_sub_car(){

   n.getParam ("latitude_init", latitude_init);
   n.getParam ("longitude_init", longitude_init);
   n.getParam ("h0", h0);
 
   sub =n.subscribe("/swiftnav"+n.getNamespace()+"/gps_pose", 1, &pub_sub_car::callback, this);
   pub = n.advertise<geometry_msgs::Vector3Stamped>("enu", 1);
   pub_odom = n.advertise<nav_msgs::Odometry>("odom", 10);

   name_space=n.getNamespace();
   name_space.erase(0,1);
//conta=0;
 }


 void callback(const sensor_msgs::NavSatFix::ConstPtr& msg){
  ROS_INFO("Input position: [%f,%f, %f]", msg->latitude, msg->longitude,msg->altitude);

    // fixed values

  double a = 6378137;
  double b = 6356752.3142;
  double f = (a - b) / a;
  double e_sq = f * (2-f);
  float deg_to_rad = 0.0174533;

    // input data from msg
  float latitude = msg->latitude;
  float longitude = msg->longitude;
  float h = msg->altitude;

  if (latitude==0 && longitude==0 && h==0){

   ROS_INFO("GPS not found");


   p.header.stamp = ros::Time::now();
   p.header.frame_id = "id"+name_space;
   p.vector.x=std::numeric_limits<float>::quiet_NaN();
   p.vector.y=std::numeric_limits<float>::quiet_NaN();
   p.vector.z=std::numeric_limits<float>::quiet_NaN();
   pub.publish(p);

 }
 else{
      
      // fixed position already defined
  ROS_INFO("values: %f %f %f",latitude_init,longitude_init,h0);


      //lla to ecef
  float lamb = deg_to_rad*(latitude);
  float phi = deg_to_rad*(longitude);
  float s = sin(lamb);
  float N = a / sqrt(1 - e_sq * s * s);

  float sin_lambda = sin(lamb);
  float  cos_lambda = cos(lamb);
  float  sin_phi = sin(phi);
  float  cos_phi = cos(phi);

  float  x = (h + N) * cos_lambda * cos_phi;
  float  y = (h + N) * cos_lambda * sin_phi;
  float  z = (h + (1 - e_sq) * N) * sin_lambda;

  ROS_INFO("ECEF position: [%f,%f, %f]", x, y,z);


      // ecef to enu

  lamb = deg_to_rad*(latitude_init);
  phi = deg_to_rad*(longitude_init);
  s = sin(lamb);
  N = a / sqrt(1 - e_sq * s * s);

  sin_lambda = sin(lamb);
  cos_lambda = cos(lamb);
  sin_phi = sin(phi);
  cos_phi = cos(phi);

  float  x0 = (h0 + N) * cos_lambda * cos_phi;
  float  y0 = (h0 + N) * cos_lambda * sin_phi;
  float  z0 = (h0 + (1 - e_sq) * N) * sin_lambda;

  float xd = x - x0;
  float  yd = y - y0;
  float  zd = z - z0;

  float  xEast = -sin_phi * xd + cos_phi * yd;
  float  yNorth = -cos_phi * sin_lambda * xd - sin_lambda * sin_phi * yd + cos_lambda * zd;
  float  zUp = cos_lambda * cos_phi * xd + cos_lambda * sin_phi * yd + sin_lambda * zd;



  ROS_INFO("ENU position: [%f,%f, %f]", xEast, yNorth,zUp);


  p.header.stamp = ros::Time::now();
  p.header.frame_id = "id_"+name_space;
  p.vector.x=xEast;
  p.vector.y=yNorth;
  p.vector.z=zUp;

  pub.publish(p);


   odom.header.stamp = ros::Time::now();
   odom.header.frame_id = "map";
   odom.pose.pose.position.x =xEast/scale_factor;
   odom.pose.pose.position.y = yNorth/scale_factor;
   odom.pose.pose.position.z = zUp/scale_factor;
   odom.child_frame_id = "odom_"+name_space;

   pub_odom.publish(odom);


  transform.setOrigin( tf::Vector3(xEast/scale_factor, yNorth/scale_factor,zUp/scale_factor) );

  tf::Quaternion q;
  q.setRPY(0, 0, 0);
  transform.setRotation(q);

  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "tf_"+name_space));

}
}
};

int main(int argc, char **argv){


	ros::init(argc, argv, "listener");
  ros::NodeHandle n; 
  pub_sub_car my_pub_sub;


  ros::spin();

  return 0;
}
