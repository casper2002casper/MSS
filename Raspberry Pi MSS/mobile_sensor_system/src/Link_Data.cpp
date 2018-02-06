#include <ros/ros.h>
#include <mobile_sensor_system/temperature.h>
#include <mobile_sensor_system/relativeHumidity.h>
#include <mobile_sensor_system/measurementData.h>
#include <mobile_sensor_system/currentTime.h>
#include <mobile_sensor_system/lightIntensity.h>
#include <mobile_sensor_system/par.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h> //agv topic: 'amcl_pose'
#include <geometry_msgs/Twist.h> //agv topic: 'cmd_vel'
#define SEPARATION_SYMBOL ";"
#define SEP SEPARATION_SYMBOL
#define RATE 0.5
ros::Publisher measurement_Data_pub;
bool timeReceived=false, temperatureReceived = false,relativeHumidityReceived=false, lightIntensityReceived =false, agvPositionReceived=false, agvVelocityReceived=false, parReceived=false;;
mobile_sensor_system::measurementData measurementData;

void checkMeasurementDataMessage(){
	if(timeReceived && temperatureReceived && relativeHumidityReceived && lightIntensityReceived && parReceived){// && agvPositionReceived && agvVelocityReceived){
	  timeReceived=false;
	  temperatureReceived = false;
	  relativeHumidityReceived=false;
	  lightIntensityReceived =false;
	  parReceived = false;
	  agvPositionReceived=false;
	  agvVelocityReceived=false;
	  measurement_Data_pub.publish(measurementData);
	}
}

void agvPositionCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
	//ROS_INFO("pose x: %f",msg->pose.pose.position.x);
	measurementData.position[0] = msg->pose.pose.position.x;
	measurementData.position[1] = msg->pose.pose.position.y;
	measurementData.position[2] = msg->pose.pose.position.z;
	agvPositionReceived = true;
	//ROS_INFO("agv pos: true");
checkMeasurementDataMessage();
}

void agvVelocityCallback(const geometry_msgs::Twist::ConstPtr& msg){
	measurementData.velocity[0] = msg->linear.x;
	measurementData.velocity[1] = msg->linear.y;
	measurementData.velocity[2] = msg->linear.z;
	agvVelocityReceived = true;
        //ROS_INFO("agv vel: true");
checkMeasurementDataMessage();
}
void currentTimeCallback(const mobile_sensor_system::currentTime::ConstPtr& msg){
   std::ostringstream oss;
   oss<<(int)msg->day<<"-"<<(int)msg->month<<"-"<<(int)msg->year<<SEP<<(int)msg->hour<<":"<<(int)msg->minute<<":"<<(int)msg->second; 
   measurementData.dateTime =oss.str();
   timeReceived = true;
   checkMeasurementDataMessage();
}

void temperatureCallback(const mobile_sensor_system::temperature::ConstPtr& msg){
  measurementData.temp = msg->temp;
  temperatureReceived = true; 
  checkMeasurementDataMessage();
}

void relativeHumidityCallback(const mobile_sensor_system::relativeHumidity::ConstPtr& msg){
  measurementData.relativeHum = msg->relativeHum;
  relativeHumidityReceived = true;
  checkMeasurementDataMessage();
}

void lightIntensityCallback(const mobile_sensor_system::lightIntensity::ConstPtr& msg){
  measurementData.lightInt = msg->lightInt;
  lightIntensityReceived = true;
  checkMeasurementDataMessage();
}

void parCallback(const mobile_sensor_system::par::ConstPtr& msg){
  measurementData.par = msg->par;
  parReceived = true;
  checkMeasurementDataMessage();
}

int main(int argc, char** argv){
  ros::init(argc, argv, "Link_Data_Node");
  ros::NodeHandle n;
  //for test without agv:
	measurementData.position[0] = 0.0;
	measurementData.position[1] = 0.0;
	measurementData.position[2] = 0.0;

	measurementData.velocity[0] = 0.0;
	measurementData.velocity[1] = 0.0;
	measurementData.velocity[2] = 0.0;
  //end 
  measurement_Data_pub = n.advertise<mobile_sensor_system::measurementData>("measurementData", 1000);
  ros::Subscriber current_Time_sub = n.subscribe("currentTime", 1000, currentTimeCallback);
  ros::Subscriber temperature_sub = n.subscribe("temperature", 1000, temperatureCallback);
  ros::Subscriber relative_Humidity_sub = n.subscribe("relativeHumidity", 1000, relativeHumidityCallback);
  ros::Subscriber light_Intensity_sub = n.subscribe("lightIntensity", 1000, lightIntensityCallback);
  ros::Subscriber par_sub = n.subscribe("par", 1000, parCallback);
  ros::Subscriber agv_Pos_sub = n.subscribe("amcl_pose", 1000, agvPositionCallback);
  ros::Subscriber agv_Vel_sub = n.subscribe("cmd_vel", 1000, agvVelocityCallback);
  ros::spin();
  return 0;
}
