//-----------------------------------------------------
//
//	Authors: Gerwin Kraak, Huig-Jan Meijvogel hebben hun best gedaan... 
//  MAAR Joeri Verkerk en Casper Pennings hebben het bijna soort van gefixt
//	Group: Smart Sensor Systems V2
//-----------------------------------------------------

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "sensor_msgs/JointState.h"
#include "ackermann_msgs/AckermannDriveStamped.h"
#include <mobile_sensor_system/QueueTrigger.h>
#include <mobile_sensor_system/action_command.h>
#include <mobile_sensor_system/start_command.h>
#include <mobile_sensor_system/stop_command.h>
#include <mobile_sensor_system/pause_command.h>
#include <mobile_sensor_system/resume_command.h>
#include <mobile_sensor_system/measure_command.h>
#include <mobile_sensor_system/control_status.h>
#include <unistd.h>
#include <sstream>
#include <math.h> 

//Variables needed for communication AGV
ros::Publisher speed_pub;
geometry_msgs::Pose agv_current;

//Variables needed for driving
bool do_measurement,paused;
float measure_distance, brake_distance, driving_distance;
float measure_position, brake_position, driving_position;
float driving_speed,measure_speed,measure_time;
float acceleration;
int status = mobile_sensor_system::control_status::IDLE;
bool start = false;

//Callback function
void AGV_Pose_Callback(const sensor_msgs::JointState::ConstPtr& msg)//Callback from the AGV with the distance moved
{
  agv_current.position.x = msg->position[0] * 0.055;//Convert radials to distance
  //ROS_INFO("Current position(x): [%f]", agv_current.position.x);
} 


void action_command_Callback(const mobile_sensor_system::action_command::ConstPtr& msg)//When a drive command is recieved
{
  measure_speed = msg->measure_speed;
  driving_speed = msg->driving_speed;
  do_measurement = msg->do_measurement;
  acceleration = msg->acceleration;
  measure_time = msg->measure_time;
  //Calculate the distances the system should drive
  measure_distance = measure_speed * measure_time;
  brake_distance = (pow(driving_speed - measure_speed, 2.0) / (2 * msg->deacceleration)) + msg->marge * measure_speed;
  driving_distance = msg->distance - measure_distance - brake_distance;
  
  driving_position = agv_current.position.x + driving_distance;
  brake_position = driving_position + brake_distance;
  measure_position = brake_position + measure_distance;
  
  status = mobile_sensor_system::control_status::DRIVING;
  ROS_INFO("Received action command");
  ROS_INFO("Start Pos: [%f]",agv_current.position.x);
  ROS_INFO("Drive Pos: [%f]",driving_position);
  ROS_INFO("Brake pos: [%f]",brake_position);
  ROS_INFO("Measure_pos: [%f]", measure_position);
}

void pause_command_Callback(const mobile_sensor_system::pause_command::ConstPtr& msg)//When a pause command is recieved
{
  paused = true;
  ROS_INFO("Received pause command");
}

void resume_command_Callback(const mobile_sensor_system::resume_command::ConstPtr& msg)//When a resume command is recieved
{
  paused = false;
  ROS_INFO("Received resume command");
}

void start_command_Callback(const mobile_sensor_system::start_command::ConstPtr& msg)//When a start command is recieved
{
  start = true;
  ROS_INFO("Received start command");
}

void stop_command_Callback(const mobile_sensor_system::stop_command::ConstPtr& msg)//When a stop command is recieved
{
  start = false;
  status = mobile_sensor_system::control_status::IDLE;
  ROS_INFO("Received stop command");
}

void set_speed_accel(float speed, float accel){
    //ROS_INFO("publishing now speed: [%f]",speed);
    ackermann_msgs::AckermannDriveStamped move_msg;
    move_msg.header.stamp=ros::Time::now(); 
    move_msg.drive.speed = speed;
    move_msg.drive.acceleration = accel;
    speed_pub.publish(move_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Control_AGV");
  ros::NodeHandle n;
  ros::Time time_now=ros::Time::now();
  geometry_msgs::PoseStamped agv_goal;
  //Create the publisher and subscriber
  //AGV===================================================================================================
  speed_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>("move", 1000);
  ros::Subscriber amcl_pose_sub = n.subscribe("joint_states", 1000, AGV_Pose_Callback);
  //MSS===================================================================================================
  ros::Publisher queue_trigger_pub = n.advertise<mobile_sensor_system::QueueTrigger>("QueueTrigger", 1000);
  ros::Publisher measure_trigger_pub = n.advertise<mobile_sensor_system::measure_command>("measure_command", 1000);
  ros::Subscriber action_command_sub = n.subscribe("action_command", 1000, action_command_Callback);
  ros::Subscriber pause_command_sub = n.subscribe("pause_command", 1000, pause_command_Callback);
  ros::Subscriber resume_command_sub = n.subscribe("resume_command", 1000, resume_command_Callback);
  ros::Subscriber start_command_sub = n.subscribe("start_command", 1000, start_command_Callback);
  ros::Subscriber stop_command_sub = n.subscribe("stop_command", 1000, stop_command_Callback);
  ros::Publisher measure_pub = n.advertise<mobile_sensor_system::measure_command>("measure_command", 10);
  ros::Publisher status_pub = n.advertise<mobile_sensor_system::control_status>("control_status", 10);
  //======================================================================================================
  
  agv_current.position.x = 0.0;
  //Waiting for positional data from AGV  
  ROS_INFO("Waiting for AGV...");
  while (agv_current.position.x == 0.0 && ros::ok()){//Callback changes the position
  	ros::spinOnce();
  	sleep(1);
  }
  ROS_INFO("Connected to AGV");
  //Main loop of program
  mobile_sensor_system::control_status currentstatus;
  while (ros::ok())
  {
    currentstatus.status = status;
    switch(status){//Switch state for every state
      
      case(mobile_sensor_system::control_status::IDLE)://Status is idle
      {
        //Wait for new command and set speed to 0
        status_pub.publish(currentstatus);
        mobile_sensor_system::QueueTrigger triggerQueue;
        queue_trigger_pub.publish(triggerQueue);
        ros::Duration(0.1).sleep();
        ros::spinOnce();
        if(status == mobile_sensor_system::control_status::IDLE){
          set_speed_accel(0,acceleration);
        }
        break;
      }
      
      case(mobile_sensor_system::control_status::DRIVING):
      {
        if(start){//Check if the start bool is set
          //Drive with driving speed to the driving position
          ROS_INFO("Driving");
          agv_goal.pose.position.x = driving_position;
          while (agv_current.position.x < agv_goal.pose.position.x){
            if(!start){
              break;
            } 
            while(paused){//While the paused bool is set wait with speed 0
              set_speed_accel(0,acceleration);
              ros::spinOnce();
              ros::Duration(0.1).sleep();
            }
            ros::spinOnce();
            set_speed_accel(driving_speed,acceleration);
            ros::Duration(0.1).sleep();
            status_pub.publish(currentstatus);
          }
          status = mobile_sensor_system::control_status::SLOWING;
        }
        break;
      } 
      
      case(mobile_sensor_system::control_status::SLOWING):
      {
        //Slow down to the measure speed
        ROS_INFO("Slowing down");
        agv_goal.pose.position.x = brake_position;
        while (agv_current.position.x < agv_goal.pose.position.x ){
          if(!start){
            break;
          } 
          while(paused){
            set_speed_accel(0,acceleration);
            ros::spinOnce();
            ros::Duration(0.1).sleep();
          }
          ros::spinOnce();
          set_speed_accel(measure_speed,acceleration);
          ros::Duration(0.1).sleep();
          status_pub.publish(currentstatus);
        }
        status = mobile_sensor_system::control_status::MEASURING;
        break;
      }
      
      case(mobile_sensor_system::control_status::MEASURING):
      {
        //Start a measurement and drive with measurement speed to the measure position
        ROS_INFO("Measuring");
        mobile_sensor_system::measure_command measure_commando;
        measure_commando.max_measure_time = measure_time;
    	  if(do_measurement) measure_pub.publish(measure_commando);
        agv_goal.pose.position.x = measure_position;
        while (agv_current.position.x < agv_goal.pose.position.x ){
          if(!start){
            break;
          } 
          while(paused){
            set_speed_accel(0,acceleration);
            ros::spinOnce();
            ros::Duration(0.1).sleep();
          }
          ros::spinOnce();
          set_speed_accel(measure_speed,acceleration);
          ros::Duration(0.1).sleep();
          status_pub.publish(currentstatus);
        }
        status = mobile_sensor_system::control_status::IDLE;
        ROS_INFO("Idling");
        break;
      }  
      
      default:
      {
				ROS_INFO("Invalid status");
				status = mobile_sensor_system::control_status::IDLE;
				break;
      }
      
    }
    //spin to react on incoming message
    ros::spinOnce();
    ros::Duration(0.2).sleep();
  }
  return 0;
}



























































//   //loop of program
//   while (ros::ok() && count_value<5)
//   {
    
//     if (1){//x_Coordinate_next <= x_Coordinate_cur){
//       //geometry_msgs::PoseStamped agv_goal;
//       x_Coordinate_next = x_Coordinate_cur;
//       x_Coordinate_next += 5.0;	
//       agv_goal.pose.position.x=x_Coordinate_cur+1;	 	//in meters??
//       agv_goal.pose.position.y=y_Coordinate_cur;
//       agv_goal.pose.orientation.z=z_orientation_cur;
//       agv_goal.pose.orientation.w=w_orientation_cur;
      
//       time_now=ros::Time::now();
//       agv_goal.header.stamp=time_now;
//       agv_goal.header.frame_id="map";
//       ROS_INFO("Next Position(x): [%f]", x_Coordinate_next);
//       chatter_pub.publish(agv_goal);
//       count_value+=1;
//     }
   
//     //spin to react on incoming message
//     ros::spinOnce();
//     sleep(3);
//   }
//   return 0;
// } 