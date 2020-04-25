  #include "ros/ros.h"
  #include "std_msgs/String.h"
  #include "geometry_msgs/QuaternionStamped.h"
  #include "lla2enu/custom.h"
  #include <message_filters/subscriber.h>
  #include <message_filters/time_synchronizer.h>
  #include <message_filters/sync_policies/exact_time.h>
  #include <message_filters/sync_policies/approximate_time.h>
  #include "lla2enu/DistanceCalculator.h"



class collettore
{


private:
  ros::NodeHandle n;
  message_filters::Subscriber<geometry_msgs::QuaternionStamped> sub1;
  message_filters::Subscriber<geometry_msgs::QuaternionStamped> sub2;
  typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::QuaternionStamped, geometry_msgs::QuaternionStamped> MySyncPolicy;
  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync;
  ros::ServiceClient client;
  ros::Publisher custom_pub;
  lla2enu::DistanceCalculator srv;


public:
  collettore(){
    sub1.subscribe(n, "enu_front", 1);
    sub2.subscribe(n, "enu_obs", 1);
    client = n.serviceClient<lla2enu::DistanceCalculator>("distance_calc");
<<<<<<< HEAD
    custom_pub = n.advertise<lla2enu::custom>("custum_message",1);
=======
    custom_pub = n.advertise<lla2enu::custom>("custom_message");
>>>>>>> a1c547618b8dbd7e5946193421026a56ebbfdb08
    sync.reset(new Sync(MySyncPolicy(10), sub1, sub2));
    sync->registerCallback(boost::bind(&collettore::callback,this, _1, _2));

  }


  void callback(const geometry_msgs::QuaternionStampedConstPtr& front_msg, const geometry_msgs::QuaternionStampedConstPtr& obs_msg)
  {
    ROS_INFO ("Received two messages: (%f,%f,%f ,%f) and (%f,%f,%f,%f)", front_msg->quaternion.x, front_msg->quaternion.y,front_msg->quaternion.z, front_msg->quaternion.w, obs_msg->quaternion.x, obs_msg->quaternion.y,obs_msg->quaternion.z, obs_msg->quaternion.w);

    if (front_msg->quaternion.w == 0 || obs_msg->quaternion.w == 0){

      ROS_INFO ("GPS Missing ");

    }

    else{

      ROS_INFO ("GPS Working ");

      srv.request.x = front_msg->quaternion.x;
      srv.request.y = front_msg->quaternion.y;
      srv.request.z = front_msg->quaternion.z;
      srv.request.x_obs = obs_msg->quaternion.x;
      srv.request.y_obs = obs_msg->quaternion.y;
      srv.request.z_obs = obs_msg->quaternion.z;

      if (client.call(srv))
      {
        ROS_INFO("Distance: %f, Flag: %s ", srv.response.distance, srv.response.flag.c_str());
        lla2enu::custom msg;
        msg.distance = srv.response.distance;
        msg.flag = srv.response.flag.c_str();
        custom_pub.publish(msg);
      }
      else
      {
        ROS_ERROR("Failed to call service distance calculator");

      }
    }
  }

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "collector");

  collettore my_collettore;

  ros::spin();

  return 0;
}
