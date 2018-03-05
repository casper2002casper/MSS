#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import lightIntensity
from TSL2591_lux import *
import time
RATE = 0.5

#------------------main----------------
def main():
	rospy.init_node("Measure_Light_Intensity_Node", anonymous=True)
	light_int_pub = rospy.Publisher("lightIntensity", lightIntensity, queue_size=1000)	
	loop_rate = rospy.Rate(RATE)
	light_intensity_value = lightIntensity()
	tsl = Tsl2591()  #=> uncomment this to use the sensor
	while not rospy.is_shutdown():
		full, ir = tsl.get_full_luminosity()# read raw values (full spectrum and ir spectrum)   #=> uncomment this to use the sensor
		lux = tsl.calculate_lux(full, ir)  # convert raw values to lux     #=> uncomment this to use the sensor
		light_intensity_value.lightInt = 35.1#round(lux,1)    #=> uncomment this to use the sensor
		light_int_pub.publish(light_intensity_value)
		loop_rate.sleep()
	
main()
