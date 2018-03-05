#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <ros/ros.h>
#include <mobile_sensor_system/measurementData.h>

#define SEPARATION_SYMBOL ";"
#define SEP SEPARATION_SYMBOL
#define FILENAME "/media/mss/MSS_USB/measurements/measurement.csv"
#define BUFFERSIZE 20
using namespace std;
using namespace mobile_sensor_system;
//string buffer[BUFFERSIZE];
vector <string> buffer;
int errorCnt=0;

void measurementDataCallback(const mobile_sensor_system::measurementData::ConstPtr& msg)
{
  std::ostringstream oss;
  string tempString;  
  /*double x,y,z,vx,vy,vz;
  float temp, relativeHum, lightInt;
  string dateTime = msg->dateTime;
  x = msg->position[0];
  y = msg->position[1];
  z = msg->position[2];
  vx = msg->velocity[0];
  vy = msg->velocity[1];
  vz = msg->velocity[2];
  temp = msg->temp;
  relativeHum = msg->relativeHum;
  lightInt = msg->lightInt; oss<<dateTime<<SEP<<x<<SEP<<y<<SEP<<z<<SEP<<vx<<SEP<<vy<<SEP<<vz<<SEP<<temp<<SEP<<relativeHum<<SEP<<lightInt<<endl;*/
  
oss<<msg->dateTime<<SEP<<(double)msg->position[0]<<SEP<<(double)msg->position[1]<<SEP<<(double)msg->position[2]<<SEP<<(double)msg->velocity[0]<<SEP<<(double)msg->velocity[1]<<SEP<<(double)msg->velocity[2]<<SEP<<(float)msg->temp<<SEP<<(float)msg->relativeHum<<SEP<<(float)msg->lightInt<<SEP<<(double)msg->par<<SEP<<(float)msg->CO2level<<endl;
  tempString = oss.str();
  ofstream myfile (FILENAME, ios::out |ios::app );
  if (myfile.is_open())
  { 
    if(errorCnt > 0){
	ROS_INFO("Saving data from buffer to csv");
    	for(int i=0;i<errorCnt;i++){
    		myfile << buffer[i];		
	}
	buffer.clear();
	errorCnt =0;
    }
    myfile << tempString;
    ROS_INFO("Saving data to csv");	
    myfile.close();
  }
  else{
    ROS_INFO("Save_Measurement_to_file: Unable to open file!");
    //cout << "Unable to open file"
    if(buffer.size()<BUFFERSIZE){
	    //buffer[errorCnt] = tempString;
	    buffer.push_back(tempString);
	    ROS_INFO("Measurement added to buffer: %s", buffer[errorCnt].c_str());
	    errorCnt++;
    }else{
	buffer.clear();
	errorCnt=0;
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Save_Measurement_To_File_Node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("measurementData", 1000, measurementDataCallback);
  ros::spin();
  return 0;
}

