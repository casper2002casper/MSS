#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <ros/ros.h>
#include <mobile_sensor_system/action_command.h>
#include <mobile_sensor_system/start_command.h>
#include <mobile_sensor_system/stop_command.h>
#include <mobile_sensor_system/pause_command.h>
#include <mobile_sensor_system/resume_command.h>
#define FILENAME "/media/mss/MSS_USB2/commands/commands.csv"
#define FILENAME_TEMP "/media/mss/MSS_USB2/commands/commands_temp.csv"

using namespace std;
using namespace mobile_sensor_system;

float32 parser[20](string data){
	float32 array[20];
	string buffer[15];
	int counter = 0;
	for (x=0;x<data.length();x++){
		if(csv_data[x] == ';'){
			array[counter] = strtof((buffer).c_str(),0);
			counter++;
			buffer.clear();
		}
		else buffer[buffer.length] = csv_data[x];
	}
	if(!buffer.empty())array[counter] = strtof((buffer).c_str(),0);
	return(array);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Read_Command_files_Node");
  ros::NodeHandle n;
  ros::Publisher action_pub = n.advertise<mobile_sensor_system::action_command>("action_command", 10);
  ros::Publisher start_pub = n.advertise<mobile_sensor_system::start_command>("start_command", 10);
  ros::Publisher stop_pub = n.advertise<mobile_sensor_system::stop_command>("stop_command", 10);
  ros::Publisher pause_pub = n.advertise<mobile_sensor_system::pause_command>("pause_command", 10);
  ros::Publisher resume_pub = n.advertise<mobile_sensor_system::resume_command>("resume_command", 10);
  while (ros::ok()){
	ifstream ip(FILENAME);
	if(ip.good()){
		ROS_INFO("foundline");
		string csv_data;
		getline(ip,csv_data,'\n');
		if(!csv_data.empty()){
			float32 parsed = parser(csv_data);
			switch(csv_data[5]){
				case('0')://Action command
					mobile_sensor_system::action_command action_commando;
					action_command.afstand = parsed[2];
					action_command.rijsnelheid = parsed[3];
					action_command.meetsnelheid = parsed[4];
					action_command.meettijd = parsed[5];
					action_command.acceleratie = parsed[6];
					action_command.deacceleratie = parsed[7];
					action_pub.publish(action_commando);
					break;	
				case('1'):
					mobile_sensor_system::start_command start_commando;
					action_command.afstand = parsed[1];
					action_pub.publish(start_commando);
					break;
	
			}			
			ofstream ip_temp(FILENAME_TEMP);
			string buf_to_temp_data;
			while(ip.good()){
				getline(ip,buf_to_temp_data,'\n');
		    		ip_temp<<buf_to_temp_data<<endl;
			}
			ip_temp.close();
		}
	}
	ip.close();
  	ros::spinOnce();
	sleep(1);
  }
  return 0;
}

