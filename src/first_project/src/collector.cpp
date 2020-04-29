  #include "ros/ros.h"
  #include "std_msgs/String.h"
  #include "geometry_msgs/Vector3Stamped.h"
  #include "first_project/custom.h"
  #include <message_filters/subscriber.h>
  #include <message_filters/time_synchronizer.h>
  #include <message_filters/sync_policies/approximate_time.h>
  #include "first_project/DistanceCalculator.h"
  #include <dynamic_reconfigure/server.h>
  #include <first_project/parametersConfig.h>



class collector
{

private:
	ros::NodeHandle n;
	message_filters::Subscriber<geometry_msgs::Vector3Stamped> sub_car;
	message_filters::Subscriber<geometry_msgs::Vector3Stamped> sub_obs;
	typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::Vector3Stamped, geometry_msgs::Vector3Stamped> MySyncPolicy;
	typedef message_filters::Synchronizer<MySyncPolicy> Sync;
	boost::shared_ptr<Sync> sync;
	ros::ServiceClient client;
	ros::Publisher custom_pub;
	first_project::DistanceCalculator srv;
	first_project::custom msg;

	dynamic_reconfigure::Server<first_project::parametersConfig> server;
	dynamic_reconfigure::Server<first_project::parametersConfig>::CallbackType f;

	int safe;
	int unsafe;

public:
	collector(){

		sub_car.subscribe(n, "front/enu", 1);
		sub_obs.subscribe(n, "obs/enu", 1);
		client = n.serviceClient<first_project::DistanceCalculator>("distance_calc");
		custom_pub = n.advertise<first_project::custom>("custom_message",10);
		sync.reset(new Sync(MySyncPolicy(10), sub_car, sub_obs));
		sync->registerCallback(boost::bind(&collector::callback,this, _1, _2));
		n.getParam ("/unsafe", unsafe);
		n.getParam ("/safe", safe);

		f = boost::bind(&collector::dynamic_callback,this, _1);
		server.setCallback(f);

	}


	void callback(const geometry_msgs::Vector3StampedConstPtr& front_msg, const geometry_msgs::Vector3StampedConstPtr& obs_msg)
	{
		if (isnan(front_msg->vector.x) || isnan(obs_msg->vector.x)){

			ROS_ERROR ("GPS Missing ");
			msg.distance = std::numeric_limits<float>::quiet_NaN();
      		msg.flag = "Invalid Distance"; //Cosa fargli fare nel caso la distanza è nulla (possiamo anche ritornargli l' ultimo valore della flag)
     		custom_pub.publish(msg);
  		}

		else{

			ROS_INFO ("GPS Retraived ");

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

			
			else{
				ROS_ERROR("Failed to call service: distance_calculator");
			}
		}
	}

	void dynamic_callback ( first_project::parametersConfig &config) {
		ROS_INFO("Reconfigure Request: %d, %d",config.safe_param, config.unsafe_param);
		safe = config.safe_param;
		unsafe = config.unsafe_param;
	}
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "collector");

	collector my_collector;

	ros::spin();

	return 0;
}
