#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import lightIntensity
from TSL2591_lux import *
import time
RATE = 2

#------------------main----------------
def main():
	# initialization
	rospy.init_node("Measure_Light_Intensity_Node", anonymous=True)
	light_int_pub = rospy.Publisher("lightIntensity", lightIntensity, queue_size=1000)	
	loop_rate = rospy.Rate(RATE)
	light_intensity_value = lightIntensity()
	sensor_attached = True
	# check if sensor is attached (could be improved!)
	try:
		tsl = Tsl2591()
	except:
		rospy.loginfo("Lux sensor not attached")
		sensor_attached = False
		
	light_intensity_value.sensor_attached = sensor_attached;
	
	while not rospy.is_shutdown():
		if(sensor_attached):
			full, ir = tsl.get_full_luminosity()# read raw values (full spectrum and ir spectrum)
			lux = tsl.calculate_lux(full, ir)  # convert raw values to lux 
			light_intensity_value.lightInt = round(lux,1)    
		else:
			light_intensity_value.lightInt = 0.0
		# publish values
		light_int_pub.publish(light_intensity_value)
		loop_rate.sleep()
	
main()
