#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "ros/ros.h"
#include <mobile_sensor_system/QueueTrigger.h>
#include <mobile_sensor_system/action_command.h>
#include <mobile_sensor_system/start_command.h>
#include <mobile_sensor_system/stop_command.h>
#include <mobile_sensor_system/pause_command.h>
#include <mobile_sensor_system/resume_command.h>
#define FILENAME "/media/mss/MSS_USB2/commands/Que_commands.csv"
#define FILENAME_TEMP "/media/mss/MSS_USB2/commands/Que_commands_temp.csv"
ros::Publisher action_pub;
ros::Publisher start_pub;
ros::Publisher stop_pub;
ros::Publisher pause_pub;
ros::Publisher resume_pub;

void QueueTriggerCallback(const mobile_sensor_system::QueueTrigger::ConstPtr& msg){
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
				default:
					ROS_INFO("INVALID command type");
					break;
	
			}
			if(msg->clear_first){			
				ofstream ip_temp(FILENAME_TEMP);
				string buf_to_temp_data;
				while(ip.good()){
					getline(ip,buf_to_temp_data,'\n');
			    		ip_temp<<buf_to_temp_data<<endl;
				}
				ip_temp.close();
				ip.close();
				rename(FILENAME_TEMP,FILENAME);
			}
		}
	}
	ip.close();	
}

int main(int argc, char** argv){
	ros::init(argc, argv, "Queue_List");
	ros::NodeHandle n;
	ros::Subscriber queue_trigger_sub = n.subscribe("QueueTrigger", 1000, QueueTriggerCallback);
	action_pub = n.advertise<mobile_sensor_system::action_command>("action_command", 10);
	start_pub = n.advertise<mobile_sensor_system::start_command>("start_command", 10);
	stop_pub = n.advertise<mobile_sensor_system::stop_command>("stop_command", 10);
	pause_pub = n.advertise<mobile_sensor_system::pause_command>("pause_command", 10);
	resume_pub = n.advertise<mobile_sensor_system::resume_command>("resume_command", 10);
	ros::spin();
	return 0;
}
