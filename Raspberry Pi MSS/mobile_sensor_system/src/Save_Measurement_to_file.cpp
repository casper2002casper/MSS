#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <ros/ros.h>
#include <mobile_sensor_system/measurementData.h>

#define SEPARATION_SYMBOL ";"
#define SEP SEPARATION_SYMBOL
#define EXTRA_SEPERATION_SYMBOL "+"
#define ESEP EXTRA_SEPERATION_SYMBOL
#define FILENAME "/media/mss/MSS_USB7/measurements/measurement.csv" //Sometimes the USB location changes when the system is turned of while ros is running
#define BUFFERSIZE 20
using namespace std;
using namespace mobile_sensor_system;

//string buffer[BUFFERSIZE];
vector <string> buffer;
int errorCnt=0;

void measurementDataCallback(const mobile_sensor_system::measurementData::ConstPtr& msg)//Gets called when link_data transmits data
{
  std::ostringstream oss;
  string tempString;  
  //Write all data to stringstream
  oss<<msg->dateTime<<SEP<<\
  (double)msg->position[0]<<SEP<<\
  (double)msg->position[1]<<SEP<<\
  (double)msg->position[2]<<SEP<<\
  (double)msg->velocity[0]<<SEP<<\
  (double)msg->velocity[1]<<SEP<<\
  (double)msg->velocity[2]<<SEP<<
  (float)msg->temp[0]<<ESEP<<\
  (float)msg->temp[1]<<ESEP<<\
  (float)msg->temp[2]<<ESEP<<\
  (float)msg->temp[3]<<SEP<<\
  (float)msg->relativeHum[0]<<ESEP<<\
  (float)msg->relativeHum[1]<<ESEP<<\
  (float)msg->relativeHum[2]<<ESEP<<\
  (float)msg->relativeHum[3]<<SEP<<\
  (float)msg->lightInt<<SEP<<\
  (double)msg->par<<SEP<<\
  (float)msg->CO2level<<SEP<<endl;
  
  tempString = oss.str();//Convert stringstream to string
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
    }
    else{
	    buffer.clear();
	    errorCnt=0;
    }
  }
}

int main(int argc, char **argv)//Doesn't repeat
{
  ros::init(argc, argv, "Save_Measurement_To_File_Node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("measurementData", 1000, measurementDataCallback);
  ros::spin();
  return 0;
}

