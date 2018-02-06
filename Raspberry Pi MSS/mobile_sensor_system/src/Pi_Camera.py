#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import currentTime
from geometry_msgs.msg import PoseWithCovarianceStamped
from picamera import PiCamera
import time
IMAGE_LOCATION ="/media/mss/MSS_USB/images/"
pose_x=0.0
pose_y=0.0
pose_z=0.0
camera = PiCamera()

def agvPositionCallback(msg):
	global pose_x 
	pose_x = msg.pose.pose.position.x
	global pose_y 
	pose_y = msg.pose.pose.position.y
	global pose_z 
	pose_z = msg.pose.pose.position.z

def currentTimeCallback(msg):
	camera.annotate_text =str(msg.day) + "-"+ str(msg.month) + "-"+str(msg.year)+ " "+str(msg.hour)+":"+str(msg.minute)+":"+str(msg.second) + "x:"+str(pose_x)+ " y:"+str(pose_y)+" z:"+str(pose_z)

	filename =IMAGE_LOCATION+ str(msg.day) + "-"+ str(msg.month) + "-"+str(msg.year)+ " "+str(msg.hour)+"."+str(msg.minute)+"."+str(msg.second) + " x_"+str(pose_x)+ " y_"+str(pose_y)+" z_"+str(pose_z)+ ".png"
	#print(filename +'\n')
	camera.capture(filename)


#------------------main----------------
def main():
	rospy.init_node("Take_Save_Images_Node", anonymous=True)
	currentTime_sub = rospy.Subscriber("currentTime", currentTime, currentTimeCallback)
	agvPosition_sub = rospy.Subscriber("amcl_pose", PoseWithCovarianceStamped, agvPositionCallback)
	rospy.spin()	
	
main()
