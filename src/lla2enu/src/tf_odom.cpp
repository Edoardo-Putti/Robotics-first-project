#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/NavSatFix.h"
#include <math.h>
#include "geometry_msgs/Vector3Stamped.h"
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>

class pub_sub_obstacle
{


private:

  ros::NodeHandle n;
  ros::Subscriber sub1;
  ros::Subscriber sub2;

  nav_msgs::Odometry odom;
  ros::Publisher pub_odom;

  nav_msgs::Odometry odom_o;
  ros::Publisher pub_odom_o;

  tf::Transform transform;
  tf::TransformBroadcaster br;

  tf::Transform transform_o;
  tf::TransformBroadcaster br_o;


  	std::string input1;
    std::string input2;


public:
 pub_sub_obstacle(){
     	n.getParam ("input1", input1);
		n.getParam ("input2", input2);
   sub1 =n.subscribe(input1, 1, &pub_sub_obstacle::callback_f, this);
   sub2 =n.subscribe(input2, 1, &pub_sub_obstacle::callback_o, this);
   pub_odom = n.advertise<nav_msgs::Odometry>("/odom_front", 10);
   pub_odom_o = n.advertise<nav_msgs::Odometry>("/odom_obs", 10);

 }


 void callback_f(const geometry_msgs::Vector3StampedConstPtr& msg){
  ROS_INFO("Input position: [%f,%f, %f]", msg->vector.x, msg->vector.y ,msg->vector.z);

    float x=msg->vector.x/100;
  float y=msg->vector.y/100;
  float z=msg->vector.z/100;

 if (isnan(msg->vector.x)){}
else{
  odom.header.stamp = ros::Time::now();
  odom.header.frame_id = "map";
  odom.pose.pose.position.x =x ;
  odom.pose.pose.position.y = y;
  odom.pose.pose.position.z = z;
  odom.child_frame_id = "odom_front";

  pub_odom.publish(odom);


  tf::Transform transform;
  transform.setOrigin( tf::Vector3(x,y,z) );

  tf::Quaternion q;
  q.setRPY(0, 0, 0);
  transform.setRotation(q);

  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "tf_front"));

 }
}


 void callback_o(const geometry_msgs::Vector3StampedConstPtr& msg){
  ROS_INFO("Input position: [%f,%f, %f]", msg->vector.x, msg->vector.y ,msg->vector.z);
  float x=msg->vector.x/100;
  float y=msg->vector.y/100;
  float z=msg->vector.z/100;

if (isnan(msg->vector.x)){}
else{
  odom_o.header.stamp = ros::Time::now();
  odom_o.header.frame_id = "map";
  odom_o.pose.pose.position.x =x ;
  odom_o.pose.pose.position.y = y;
  odom_o.pose.pose.position.z = z;
  odom_o.child_frame_id = "odom_obs";

  pub_odom_o.publish(odom_o);


  tf::Transform transform;
  transform_o.setOrigin( tf::Vector3(x, y, z) );

  tf::Quaternion q;
  q.setRPY(0, 0, 0);
  transform.setRotation(q);

  br_o.sendTransform(tf::StampedTransform(transform_o, ros::Time::now(), "map", "tf_obs"));

}
}

};

int main(int argc, char **argv){

	ros::init(argc, argv, "tf_odom");

  pub_sub_obstacle my_pub_sub;


  ros::spin();

  return 0;
}
