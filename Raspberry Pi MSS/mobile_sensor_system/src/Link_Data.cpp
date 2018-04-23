#include <ros/ros.h>
#include <ros/console.h>
#include <mobile_sensor_system/QueueTrigger.h>
#include <mobile_sensor_system/temperature.h>
#include <mobile_sensor_system/relativeHumidity.h>
#include <mobile_sensor_system/measurementData.h>
#include <mobile_sensor_system/currentTime.h>
#include <mobile_sensor_system/lightIntensity.h>
#include <mobile_sensor_system/measure_command.h>
#include <mobile_sensor_system/stop_command.h>
#include <mobile_sensor_system/CO2.h>
#include <mobile_sensor_system/par.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h> //agv topic: 'amcl_pose'
#include <geometry_msgs/Twist.h> //agv topic: 'cmd_vel'
#define SEPARATION_SYMBOL ";"
#define SEP SEPARATION_SYMBOL
#define RATE 0.5

int loopcycles = 10;
bool continuous_measurement = false;

ros::Publisher measurement_Data_pub;
ros::Publisher Queue_pub;
mobile_sensor_system::measurementData measurementData;

bool timeReceived=false, 
     temperatureReceived = false,
     relativeHumidityReceived=false, 
     lightIntensityReceived =false, 
     agvPositionReceived=false, 
     agvVelocityReceived=false, 
     parReceived=false,
     CO2Received=false;


void agvPositionCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
  //get AGV position
  //ROS_INFO("pose x: %f",msg->pose.pose.position.x);
  measurementData.position[0] = msg->pose.pose.position.x;
  measurementData.position[1] = msg->pose.pose.position.y;
  measurementData.position[2] = msg->pose.pose.position.z;
  agvPositionReceived = true;
  //ROS_INFO("agv pos: true");
}


void agvVelocityCallback(const geometry_msgs::Twist::ConstPtr& msg){
  //get AGV velocities
  measurementData.velocity[0] = msg->linear.x;
  measurementData.velocity[1] = msg->linear.y;
  measurementData.velocity[2] = msg->linear.z;
  agvVelocityReceived = true;
  //ROS_INFO("agv vel: true");
}


void currentTimeCallback(const mobile_sensor_system::currentTime::ConstPtr& msg){
  //get current time
  std::ostringstream oss;
  oss<<(int)msg->day<<"-"<<(int)msg->month<<"-"<<(int)msg->year<<SEP<<(int)msg->hour<<":"<<(int)msg->minute<<":"<<(int)msg->second; 
  measurementData.dateTime =oss.str();
  timeReceived = true;
}


void measure_commandCallback(const mobile_sensor_system::measure_command::ConstPtr& msg){
  //Combine all measurement data and send to "Save_Measurement_to_file" Node
  ros::Time begin;
  continuous_measurement = msg->continuous_measurement;
  do{
    //Check if all sensors have completed their measurement. 
    //If not, check for a certain amount of time till all sensors did.
    begin = ros::Time::now(); 
    if(msg->max_measure_time > 0.0){
      bool data_send = false;
      
      timeReceived=false;
      temperatureReceived = false;
      relativeHumidityReceived=false;
      lightIntensityReceived =false;
      parReceived = false;
      agvPositionReceived=false;
      agvVelocityReceived=false;
      CO2Received = false;
      
      for (int i=0;i<loopcycles;i++){
        ros::spinOnce();
        ros::Duration(msg->max_measure_time / float(loopcycles)).sleep();
        if(timeReceived && temperatureReceived && relativeHumidityReceived && lightIntensityReceived && parReceived  && CO2Received){// && agvPositionReceived && agvVelocityReceived){
      	  timeReceived=false;
      	  temperatureReceived = false;
      	  relativeHumidityReceived=false;
      	  lightIntensityReceived =false;
      	  parReceived = false;
      	  agvPositionReceived=false;
      	  agvVelocityReceived=false;
      	  CO2Received = false;
      	  measurement_Data_pub.publish(measurementData);
      	  data_send = true;
      	  ROS_INFO("Measurement completed");
      	  break;
        }
      }
      if(!data_send){
        ROS_WARN("Not able to send sensor data for sensor:");
        if (!timeReceived) ROS_WARN("Time");
        if (!temperatureReceived) ROS_WARN("Temperature");
        if (!relativeHumidityReceived) ROS_WARN("Humidity");
        if (!lightIntensityReceived) ROS_WARN("Lux");
        if (!parReceived) ROS_WARN("Par");
        if (!CO2Received) ROS_WARN("CO2");
      }
    }
    else{
      ROS_WARN("Received measure command but measure time = 0");
    }
   
    if(msg->min_measure_time > 0.0 && (ros::Time::now() - begin < ros::Duration(msg->min_measure_time))){
      ros::Duration duration = ros::Duration(msg->min_measure_time);
      duration = begin - ros::Time::now() + duration;
      duration.sleep();
    }
  }
  //check if a continuous measurement has to be done. If so, stay in loop
  while(continuous_measurement && ros::ok());
}


void CO2Callback(const mobile_sensor_system::CO2::ConstPtr& msg){
  //get CO2 data
  measurementData.CO2level = msg->CO2level;
  CO2Received = true; 
}


void temperatureCallback(const mobile_sensor_system::temperature::ConstPtr& msg){
  //get temperature data
  for(int i=0;i<0.25*(sizeof(msg->temp))-1;i++){
    measurementData.temp[i] = msg->temp[i];
  }
  temperatureReceived = true; 
}


void relativeHumidityCallback(const mobile_sensor_system::relativeHumidity::ConstPtr& msg){
  //get relative Humidity data
  for(int i=0;i<0.25*(sizeof(msg->relativeHum))-1;i++){
    measurementData.relativeHum[i] = msg->relativeHum[i];
  }
  relativeHumidityReceived = true;
}


void lightIntensityCallback(const mobile_sensor_system::lightIntensity::ConstPtr& msg){
  //get Light Intesity data
  measurementData.lightInt = msg->lightInt;
  lightIntensityReceived = true;
}


void parCallback(const mobile_sensor_system::par::ConstPtr& msg){
  //get Par data
  measurementData.par = msg->par;
  parReceived = true;
}


void stop_command_Callback(const mobile_sensor_system::stop_command::ConstPtr& msg)
{
  //receive stop command
  continuous_measurement = false;
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
  Queue_pub = n.advertise<mobile_sensor_system::QueueTrigger>("QueueTrigger", 1000);
  ros::Subscriber current_Time_sub = n.subscribe("currentTime", 1000, currentTimeCallback);
  ros::Subscriber measure_command_sub = n.subscribe("measure_command", 1000, measure_commandCallback);
  ros::Subscriber temperature_sub = n.subscribe("temperature", 1000, temperatureCallback);
  ros::Subscriber relative_Humidity_sub = n.subscribe("relativeHumidity", 1000, relativeHumidityCallback);
  ros::Subscriber light_Intensity_sub = n.subscribe("lightIntensity", 1000, lightIntensityCallback);
  ros::Subscriber par_sub = n.subscribe("par", 1000, parCallback);
  //ros::Subscriber agv_Pos_sub = n.subscribe("amcl_pose", 1000, agvPositionCallback);
  //ros::Subscriber agv_Vel_sub = n.subscribe("cmd_vel", 1000, agvVelocityCallback);
  ros::Subscriber CO2_sub = n.subscribe("CO2", 1000, CO2Callback);
  ros::Subscriber stop_command_sub = n.subscribe("stop_command", 1000, stop_command_Callback);
  ros::spin();
  return 0;
}
