#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import CO2
from cozir.cozir import Cozir
import time
RATE = 0.5

#------------------main----------------
def main():
	rospy.init_node("Measure_CO2", anonymous=True)
	light_int_pub = rospy.Publisher("CO2", CO2, queue_size=1000)	
	loop_rate = rospy.Rate(RATE)
	CO2_value = CO2()
	c = Cozir('/dev/ttyUSB0')
	c.set_filter(16)
	c.set_autocal(is_active=false)
	CO2_calibration_factor = c.read_CO2_multiplier() * 1.0
	temperature_calibration_factor = 1.0
	humidity_calibration_factor = 1.0

	while not rospy.is_shutdown():
		starttime = time.time()
		CO2_value.CO2level = round(c.read_CO2() * CO2_calibration_factor,1)
		timedif = timme.time() - starttime
		rospy.loginfo("CO2 measure time: %s"%timedif)
		
		CO2_value.temperature = round(c.read_temperature() *temperature_calibration_factor,1)
		CO2_value.humidity = round(c.read_humidity()* humidity_calibration_factor,1)
		
		light_int_pub.publish(CO2_value)
		loop_rate.sleep()
	
main()
