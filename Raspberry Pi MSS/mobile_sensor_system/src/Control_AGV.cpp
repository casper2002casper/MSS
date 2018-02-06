//-----------------------------------------------------
//
//	Authors: Gerwin Kraak, Huig-Jan Meijvogel
//	Group: Smart Sensor Systems
//-----------------------------------------------------

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <unistd.h>
#include <sstream>

//Variables needed for current
float x_Coordinate_next =0.0;

float x_Coordinate_cur =0.0;
float y_Coordinate_cur =0.0;
float z_orientation_cur =0.0;
float w_orientation_cur=0.0;
int seq =0;

int secs=0;
int nsecs=0;

//Callback function
void ROS_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
  x_Coordinate_cur = msg->pose.pose.position.x;
  y_Coordinate_cur = msg->pose.pose.position.y;
  z_orientation_cur = msg->pose.pose.orientation.z;
  w_orientation_cur = msg->pose.pose.orientation.w;
  ROS_INFO("Current position(x): [%f]", x_Coordinate_cur);
} 


int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "Control_AGV");
  ros::NodeHandle n;
  ros::Time time_now=ros::Time::now();

  //Create the publisher and subscriber
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);
  ros::Subscriber sub = n.subscribe("amcl_pose", 1000, ROS_Callback);
  
 
  //initialize agv_goal with message type posestamped
  geometry_msgs::PoseStamped agv_goal;
  agv_goal.pose.position.x = 0.0;

  
  //Getting the starting position:  
  bool start_position = false;
  while (!start_position && ros::ok()){
	if (x_Coordinate_cur != 0.0 ){
	x_Coordinate_next = x_Coordinate_cur;
	start_position = true;
	}
	ros::spinOnce();
  }
  int count_value=0;

  //loop of program
  while (ros::ok() && count_value<5)
  {
    
    if (1){//x_Coordinate_next <= x_Coordinate_cur){
	//geometry_msgs::PoseStamped agv_goal;
	x_Coordinate_next = x_Coordinate_cur;
    	x_Coordinate_next += 5.0;	
    	agv_goal.pose.position.x=x_Coordinate_cur+1;	 	//in meters??
	agv_goal.pose.position.y=y_Coordinate_cur;
	agv_goal.pose.orientation.z=z_orientation_cur;
	agv_goal.pose.orientation.w=w_orientation_cur;
	
	time_now=ros::Time::now();
	agv_goal.header.stamp=time_now;
        agv_goal.header.frame_id="map";
    	ROS_INFO("Next Position(x): [%f]", x_Coordinate_next);
	chatter_pub.publish(agv_goal);
	count_value+=1;
    }
   
    //spin to react on incoming message
    ros::spinOnce();
    sleep(3);
    
   
  }


  return 0;
}
