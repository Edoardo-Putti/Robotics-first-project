  #include "ros/ros.h"
  #include "std_msgs/String.h"
  #include "geometry_msgs/QuaternionStamped.h"

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

  //  ros::ServiceClient<lla2enu::DistanceCalculator>("distance_calc");

    ros::ServiceClient client = n.serviceClient<lla2enu::DistanceCalculator>("distance_calc");
    lla2enu::DistanceCalculator srv;

   // ros::Subscriber sub1;
   // ros::Subscriber sub2;
  //  ros::Publisher pub;

  public:
    collettore(){
        sub1.subscribe(n, "enu_front", 1);
        sub2.subscribe(n, "enu_obs", 1);
    
   //typedef message_filters::sync_policies::ExactTime<geometry_msgs::QuaternionStamped, geometry_msgs::QuaternionStamped> MySyncPolicy;
        sync.reset(new Sync(MySyncPolicy(10), sub1, sub2));
        sync->registerCallback(boost::bind(&collettore::callback,this, _1, _2));

        }


  void callback(const geometry_msgs::QuaternionStampedConstPtr& front_msg, const geometry_msgs::QuaternionStampedConstPtr& obs_msg)
  {
    ROS_INFO ("Received two messages: (%f,%f,%f ,%f) and (%f,%f,%f,%f)", front_msg->quaternion.x, front_msg->quaternion.y,front_msg->quaternion.z, front_msg->quaternion.w, obs_msg->quaternion.x, obs_msg->quaternion.y,obs_msg->quaternion.z, obs_msg->quaternion.w);

    if (front_msg->quaternion.w == 0 || obs_msg->quaternion.w == 0){

      ROS_INFO ("banana : GPS Missing ");

    }

    else{

      ROS_INFO ("banana : GPS Funziona ");

      srv.request.x = front_msg->quaternion.x;
      srv.request.y = front_msg->quaternion.y;
      srv.request.x_obs = obs_msg->quaternion.x;
      srv.request.y_obs = obs_msg->quaternion.y;

          if (client.call(srv))
      {
            ROS_INFO("Sum: %f", srv.response.distance);
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


