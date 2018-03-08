//-----------------------------------------------------
//
//	Authors: Gerwin Kraak, Huig-Jan Meijvogel
//	Group: Smart Sensor Systems
//-----------------------------------------------------

#include "ros/ros.h"
#include <mobile_sensor_system/QueueTrigger.h>
#include <unistd.h>
#include <sstream>
#define FILENAME_CSV "/media/mss/MSS_USB2/commands/commands.csv"

void QueueTriggerCallback(const mobile_sensor_system::QueueTrigger::ConstPtr& msg){
  
}

int main(int argc, char** argv){
  ros::init(argc, argv, "Queue_List");
  ros::NodeHandle n;
  ros::Subscriber queue_trigger_sub = n.subscribe("QueueTrigger", 1000, QueueTriggerCallback);
  ros::spin();
  return 0;
}
