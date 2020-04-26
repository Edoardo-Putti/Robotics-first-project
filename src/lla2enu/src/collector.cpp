  #include "ros/ros.h"
  #include "std_msgs/String.h"
  #include "geometry_msgs/Vector3Stamped.h"
  #include "lla2enu/custom.h"
  #include <message_filters/subscriber.h>
  #include <message_filters/time_synchronizer.h>
 // #include <message_filters/sync_policies/exact_time.h>
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
  message_filters::Subscriber<geometry_msgs::Vector3Stamped> sub1;
  message_filters::Subscriber<geometry_msgs::Vector3Stamped> sub2;
  typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::Vector3Stamped, geometry_msgs::Vector3Stamped> MySyncPolicy;
  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync;
  ros::ServiceClient client;
  ros::Publisher custom_pub;
  lla2enu::DistanceCalculator srv;
  lla2enu::custom msg;

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


  void callback(const geometry_msgs::Vector3StampedConstPtr& front_msg, const geometry_msgs::Vector3StampedConstPtr& obs_msg)
  {
   // ROS_INFO ("Received two messages: (%f,%f,%f ,%f) and (%f,%f,%f,%f)", front_msg->vector.x, front_msg->vector.y,front_msg->vector.z ,obs_msg->vector.x, obs_msg->vector.y,obs_msg->vector.z);

    if (isnan(front_msg->vector.x) || isnan(obs_msg->vector.x)){

      ROS_ERROR ("GPS Missing ");
      msg.distance = std::numeric_limits<float>::quiet_NaN();
      msg.flag = "Invalid Distance"; //Cosa fargli fare nel caso la distanza è nulla (possiamo anche ritornargli l' ultimo valore della flag)
      custom_pub.publish(msg);

    }

    else{

      ROS_INFO ("GPS Working ");

      srv.request.x = front_msg->vector.x;
      srv.request.y = front_msg->vector.y;
      srv.request.z = front_msg->vector.z;
      srv.request.x_obs = obs_msg->vector.x;
      srv.request.y_obs = obs_msg->vector.y;
      srv.request.z_obs = obs_msg->vector.z;

      if (client.call(srv))
      {
        ROS_INFO("Distance: %f ", srv.response.distance);

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
