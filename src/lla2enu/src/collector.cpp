  #include "ros/ros.h"
  #include "std_msgs/String.h"
  #include "geometry_msgs/QuaternionStamped.h"
  #include "lla2enu/custom.h"
  #include <message_filters/subscriber.h>
  #include <message_filters/time_synchronizer.h>
  #include <message_filters/sync_policies/exact_time.h>
  #include <message_filters/sync_policies/approximate_time.h>
  #include "lla2enu/DistanceCalculator.h"

  #include <dynamic_reconfigure/server.h>
  #include <lla2enu/parametersConfig.h>



class collettore
{

int safe;
int unsafe;

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

  dynamic_reconfigure::Server<lla2enu::parametersConfig> server;
  dynamic_reconfigure::Server<lla2enu::parametersConfig>::CallbackType f;



public:
  collettore(){
    sub1.subscribe(n, "enu_front", 1);
    sub2.subscribe(n, "enu_obs", 1);
    client = n.serviceClient<lla2enu::DistanceCalculator>("distance_calc");
    custom_pub = n.advertise<lla2enu::custom>("custom_message",1);
    sync.reset(new Sync(MySyncPolicy(10), sub1, sub2));
    sync->registerCallback(boost::bind(&collettore::callback,this, _1, _2));
    n.getParam ("/unsafe", unsafe);
    n.getParam ("/safe", safe);

      f = boost::bind(&collettore::dynamic_callback,this, _1);
      server.setCallback(f);


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
        ROS_INFO("Distance: %f ", srv.response.distance);
        lla2enu::custom msg;
        msg.distance = srv.response.distance;
        

      if(msg.distance > safe){
        msg.flag = "Safe";
        }
          else if(msg.distance > unsafe && msg.distance <= safe){
        msg.flag = "Unsafe";
        }
          else{
        msg.flag = "Crash";
        }

        custom_pub.publish(msg);
      }

      
      else
      {
        ROS_ERROR("Failed to call service distance calculator");

      }
    }
  }

  void dynamic_callback ( lla2enu::parametersConfig &config) {
    ROS_INFO("Reconfigure Request: %d, %d",config.safe_param, config.unsafe_param);
            safe = config.safe_param;
           unsafe = config.unsafe_param;
}

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "collector");

  collettore my_collettore;

  ros::spin();

  return 0;
}
