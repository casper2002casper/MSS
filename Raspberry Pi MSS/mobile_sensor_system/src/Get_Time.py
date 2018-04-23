#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import currentTime
import datetime
RATE = 2
def main():
    pub = rospy.Publisher('currentTime', currentTime, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(RATE) 
    current_time = currentTime()
    while not rospy.is_shutdown():
        now = datetime.datetime.now()
	current_time.hour = now.hour
	current_time.minute =now.minute
	current_time.second =now.second
	current_time.year =now.year
	current_time.day =now.day
	current_time.month =now.month
        pub.publish(current_time)
        rate.sleep()

main()
