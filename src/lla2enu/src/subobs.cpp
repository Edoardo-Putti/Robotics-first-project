#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/NavSatFix.h"
#include <math.h>
#include "geometry_msgs/QuaternionStamped.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>

class pub_sub
{

/*
message structure of a quaternion 4 float x,y,z,w.
float w will be the value which will tell us if the GPS work or not.
Can't use x=0,y=0,z=0 since if i'm in the initial position i will have that
xd , yd, zd = 0 and so xEast, yNorth, and zUp equal to zero
  */

 geometry_msgs::QuaternionStamped p;
 nav_msgs::Odometry odom;

private:
ros::NodeHandle n;
ros::Subscriber sub1;
ros::Publisher pub;
ros::Publisher pub_odom;
tf::Transform transform;
tf::TransformBroadcaster br;


public:
  	pub_sub(){
  	sub1 =n.subscribe("/swiftnav/obs/gps_pose", 1, &pub_sub::callback, this);
	  pub = n.advertise<geometry_msgs::QuaternionStamped>("/enu_obs", 1);
    pub_odom = n.advertise<nav_msgs::Odometry>("/odom_obs", 10);

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

   ROS_INFO("Non ricevo il GPS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

    
      p.header.stamp = ros::Time::now();
		  p.header.frame_id = "obs";      
      p.quaternion.x=0;
      p.quaternion.y=0;
      p.quaternion.z=0;
      p.quaternion.w=0;
      pub.publish(p);
}
else{

    // fixed position
    float latitude_init;
    float longitude_init;
    float h0;

    n.getParam ("/latitude_init", latitude_init);
    n.getParam ("/longitude_init", longitude_init);
    n.getParam ("/h0", h0);

    ROS_INFO("values: %f %f %f",latitude_init,longitude_init, h0);



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
	  p.header.frame_id = "obs";  
    p.quaternion.x=xEast;
    p.quaternion.y=yNorth;
    p.quaternion.z=zUp;
    p.quaternion.w=1;


      odom.header.stamp = ros::Time::now();
      odom.header.frame_id = "map";
      odom.pose.pose.position.x =xEast/100; ;
      odom.pose.pose.position.y = yNorth/100;
      odom.pose.pose.position.z = zUp/100;
      odom.child_frame_id = "obs_odom";


    pub_odom.publish(odom);
    pub.publish(p);


  tf::Transform transform;
  transform.setOrigin( tf::Vector3(xEast/100, yNorth/100, zUp/100) );

  tf::Quaternion q;
  q.setRPY(0, 0, 0);
  transform.setRotation(q);

  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "obs_tf"));


  }
  }
};

int main(int argc, char **argv){

	ros::init(argc, argv, "listener_obstacle");

pub_sub my_pub_sub;


  	ros::spin();

  return 0;
}
