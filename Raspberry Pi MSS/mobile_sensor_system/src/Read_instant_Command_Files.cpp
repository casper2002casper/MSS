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

float32* parser(string input){//Parses csv data to float32 array
	//data[3] = ";";
	static float32 array[20];
	int counter = 0;
	string data = input.substr(5,input.length());
	printf("%s\n",data.c_str());
	string delimiter = ";";
	string token;
	size_t pos = 0;
	while ((pos = data.find(delimiter)) != std::string::npos) {
	    token = data.substr(0, pos);
	    array[counter] = stof(token);
	    counter++;
	    data.erase(0, pos + delimiter.length());
	}
	return(array);
}

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
			float32* parsed = parser(csv_data);
			switch((int) parsed[0]){
				case(0)://Action command
					mobile_sensor_system::action_command action_commando;
					action_command.metingDoen = (bool)parsed[1];
					action_command.afstand = parsed[2];
					action_command.rijsnelheid = parsed[3];
					action_command.meetsnelheid = parsed[4];
					action_command.meettijd = parsed[5];
					action_command.acceleratie = parsed[6];
					action_command.deacceleratie = parsed[7];
					action_pub.publish(action_commando);
					break;	

				case(1)://Start command
					mobile_sensor_system::start_command start_commando;
					start_command.opwarmtijd = parsed[1];
					start_pub.publish(start_commando);
					break;
				case(2)://Stop command
					mobile_sensor_system::stop_command stop_commando;
					stop_pub.publish(stop_commando);
					break;
				case(3)://Pause command
					mobile_sensor_system::pause_command pause_commando;
					pause_command.autoResume = parsed[1];
					pause_pub.publish(pause_commando);
					break;
				case(4)://Resume command
					mobile_sensor_system::resume_command resume_commando;
					resume_pub.publish(resume_commando);
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

