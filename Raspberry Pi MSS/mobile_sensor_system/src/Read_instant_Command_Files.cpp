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
#include <mobile_sensor_system/measure_command.h>
#include <mobile_sensor_system/QueueTrigger.h>

#define FILENAME "/media/mss/MSS_USB7/commands/instant_commands.csv"
#define FILENAME_TEMP "/media/mss/MSS_USB7/commands/instant_commands_temp.csv"

using namespace std;
//using namespace mobile_sensor_system;

float* parser(string input){//Parses csv data to float32 array
	//data[3] = ";";
	static float array[20];
	// ROS_INFO("length array: %d", input.length());
	if(input.length() < 2) return(array);
	int counter = 0;
	string data = input.substr(3,input.length());
	//printf("%s\n",data.c_str());
	string delimiter = ";";
	string token;
	size_t pos = 0;
	while ((pos = data.find(delimiter)) != std::string::npos) {
	    token = data.substr(0, pos);
	    array[counter] = stof(token);
	    counter++;
	    data.erase(0, pos + delimiter.length());
	}
	// ROS_INFO("PARSEEDDDD");
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
  ros::Publisher measure_pub = n.advertise<mobile_sensor_system::measure_command>("measure_command", 10);
  ros::Publisher Queue_pub = n.advertise<mobile_sensor_system::QueueTrigger>("QueueTrigger", 10);
  
  
  while (ros::ok()){
	ifstream ip(FILENAME);
	if(ip.good()){
		//unpack received data
		string csv_data;
		getline(ip,csv_data,'\n');
		if(!csv_data.empty()){
			ROS_INFO("New instant item");
			float* parsed = parser(csv_data);
			//printf("Case: %d\n",csv_data[0] - '0');
			//check which command has been received
			switch(csv_data[0] - '0'){
				case(0)://Action command
					{
						mobile_sensor_system::action_command action_commando;
						action_commando.do_measurement = (bool)parsed[0];
						action_commando.distance = parsed[1];
						action_commando.driving_speed = parsed[2];
						action_commando.measure_speed = parsed[3];
						action_commando.measure_time = parsed[4];
						action_commando.acceleration = parsed[5];
						action_commando.deacceleration = parsed[6];
						action_commando.marge = parsed[7];
						action_pub.publish(action_commando);
					}
					break;	

				case(1)://Start command-
					{
						mobile_sensor_system::start_command start_commando;
						start_commando.opwarmtijd = parsed[0];
						start_pub.publish(start_commando);
						mobile_sensor_system::QueueTrigger queue_trigger;
						Queue_pub.publish(queue_trigger);
					}
					break;
				case(2)://Stop command
					{
						mobile_sensor_system::stop_command stop_commando;
						stop_pub.publish(stop_commando);
					}
					break;
				case(3)://Pause command
					{
						mobile_sensor_system::pause_command pause_commando;
						pause_commando.autoResume = parsed[0];
						pause_pub.publish(pause_commando);
					}
					break;
				case(4)://Resume command
					{
						mobile_sensor_system::resume_command resume_commando;
						resume_pub.publish(resume_commando);
					}
					break;
				case(5)://Measure command
					{
						mobile_sensor_system::measure_command measure_commando;
						measure_commando.min_measure_time = parsed[1];
						measure_commando.max_measure_time = parsed[0];
						measure_commando.continuous_measurement = parsed[2];
						measure_pub.publish(measure_commando);
					}
					break;
				default:
					{
						ROS_INFO("INVALID command type");
					}
					break;
	
			}
			ofstream ip_temp(FILENAME_TEMP);
			string buf_to_temp_data;
			while(ip.good()){
				getline(ip,buf_to_temp_data,'\n');
		    	if(!buf_to_temp_data.empty())ip_temp<<buf_to_temp_data<<endl;
			}
			ip_temp.close();
			ip.close();
			rename(FILENAME_TEMP,FILENAME);
		}
	}
	ip.close();
  	ros::spinOnce();
	sleep(1);
  }
  return 0;
}

