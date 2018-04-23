#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import temperature
from mobile_sensor_system.msg import relativeHumidity
import smbus
import time
import RPi.GPIO as GPIO
RATE = 2

#------------------main----------------
def main():
	# initialization
	rospy.init_node("Measure_Temperature_Relative_Humidity_Node", anonymous=True)
	temperature_pub = rospy.Publisher("temperature", temperature, queue_size=1)
	relative_humidity_pub = rospy.Publisher("relativeHumidity", relativeHumidity, queue_size=1)
	loop_rate = rospy.Rate(RATE)
	pins = [26,19,13,6]
	# Get I2C bus
	sht_bus = smbus.SMBus(1)
	GPIO.setmode(GPIO.BCM)
	for pin in pins:
		GPIO.setup(pin, GPIO.OUT)
		GPIO.output(pin, False)
		
	temperature_value = temperature()
	rh_value = relativeHumidity()
	sensor_attached = [True,True,True,True]
	temperature_value.sensor_attached = sensor_attached;
	while not rospy.is_shutdown():
		# get data from each sensor if it's attached
		for index , pin in enumerate(pins):
			# a simple try-except checks if the sensor is attached or not, this could be improved!
			try:
				GPIO.output(pin, True)
				sht_bus.write_i2c_block_data(0x45, 0x2C, [0x06])
				if(sensor_attached[index]):
				    	time.sleep(0.1)
				    	# SHT31 address, 0x44(68)
				    	# Read data back from 0x00(00), 6 bytes
				    	# Temp MSB, Temp LSB, Temp CRC, Humididty MSB, Humidity LSB, Humidity CRC
				    	data = sht_bus.read_i2c_block_data(0x45, 0x00, 6)
				    	GPIO.output(pin, False)
				    	# Convert the data
				    	temp = data[0] * 256 + data[1]
				    	cTemp = -45 + (175 * temp / 65535.0)
				    	humidity = 100 * (data[3] * 256 + data[4]) / 65535.0
					temperature_value.temp[index] = round(cTemp,2) 
					rh_value.relativeHum[index] = round(humidity,2)
					time.sleep(0.05)
				else:
					rospy.loginfo("Temperature %d sensor reattached",index)
					rospy.loginfo("Humidity %d sensor reattached",index)
					
					sensor_attached[index] = True
			except:
				if(sensor_attached[index]):
					rospy.loginfo("Temperature sensor %d not attached",index)
					rospy.loginfo("Humidity sensor %d not attached",index)
					
					sensor_attached[index] = False
					temperature_value.sensor_attached[index] = sensor_attached[index];#Deze zijn inderdaad altijd false
					rh_value.sensor_attached[index] = sensor_attached[index];
					
				temperature_value.temp[index] = 0.0 
				rh_value.relativeHum[index] = 0.0
			
		# publish values
		temperature_pub.publish(temperature_value)
		relative_humidity_pub.publish(rh_value)
		loop_rate.sleep()
		
main()
