#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import CO2
from cozir import Cozir
import time
RATE = 2

#------------------main----------------
def main():
	rospy.init_node("Measure_CO2", anonymous=True)
	CO2_int_pub = rospy.Publisher("CO2", CO2, queue_size=1000)
	loop_rate = rospy.Rate(RATE)#Set the refresh rate in Hertz
	CO2_value = CO2()
	sensor_attached = True
	try:#Try to connect the sensor
		c = Cozir('/dev/ttyUSB0')#Create the sensor object
		c.set_filter(16)#Set the filter to 16
	except:
		rospy.loginfo("CO2 sensor not attached")
		sensor_attached = False
	
	CO2_value.sensor_attached = sensor_attached;
	
	temperature_calibration_factor = 1.0
	humidity_calibration_factor = 1.0

	while not rospy.is_shutdown():
		if(sensor_attached):
			CO2_value.CO2level = round(c.read_CO2(),1)
			CO2_value.temperature = round(c.read_temperature() *temperature_calibration_factor,1)
			CO2_value.humidity = round(c.read_humidity()* humidity_calibration_factor,1)
		else:#If the sensor is not connected the sensor will give 0.0 measurements
			CO2_value.CO2level = 0.0
			CO2_value.temperature = 0.0
			CO2_value.humidity = 0.0
			
		CO2_int_pub.publish(CO2_value)
		loop_rate.sleep()

main()
