#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <ros/ros.h>

#define FILENAME "/media/mss/MSS_USB2/measurements/measurement.csv"

using namespace std;
using namespace mobile_sensor_system;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Read_Command_files_Node");
  ros::NodeHandle n;
  ros::spin();
  return 0;
}

