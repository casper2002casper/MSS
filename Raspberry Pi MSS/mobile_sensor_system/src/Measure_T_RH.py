#!/usr/bin/env python
import rospy
from mobile_sensor_system.msg import temperature
from mobile_sensor_system.msg import relativeHumidity
import smbus
import time
RATE = 0.5

#------------------main----------------
def main():
	rospy.init_node("Measure_Temperature_Relative_Humidity_Node", anonymous=True)
	temperature_pub = rospy.Publisher("temperature", temperature, queue_size=1000)
	relative_humidity_pub = rospy.Publisher("relativeHumidity", relativeHumidity, queue_size=1000)
	loop_rate = rospy.Rate(RATE)
	temperature_value = temperature()
	rh_value = relativeHumidity()
	# Get I2C bus
	sht_bus = smbus.SMBus(1) #=> uncomment this to use the sensor
	while not rospy.is_shutdown():	
		#uncomment the following lines of code to use the sensor:
				
		# SHT25 address, 0x40(64)
		# Send temperature measurement command
		#		0xF3(243)	NO HOLD master
		sht_bus.write_byte(0x40, 0xF3)

		time.sleep(0.5)
		# SHT25 address, 0x40(64)
		# Read data back, 2 bytes
		# Temp MSB, Temp LSB
		data0 = sht_bus.read_byte(0x40)
		data1 = sht_bus.read_byte(0x40)

		# Convert the data
		temp = data0 * 256 + data1
		cTemp= -46.85 + ((temp * 175.72) / 65536.0)
		#fTemp = cTemp * 1.8 + 32
	
		# SHT25 address, 0x40(64)
		# Send humidity measurement command
		#		0xF5(245)	NO HOLD master
		sht_bus.write_byte(0x40, 0xF5)

		time.sleep(0.5)

		# SHT25 address, 0x40(64)
		# Read data back, 2 bytes
		# Humidity MSB, Humidity LSB
		data0 = sht_bus.read_byte(0x40)
		data1 = sht_bus.read_byte(0x40)

		# Convert the data
		humidity = data0 * 256 + data1
		humidity = -6 + ((humidity * 125.0) / 65536.0)	
		
		temperature_value.temp =round(cTemp,2)  #=> uncomment this to use the sensor
		temperature_pub.publish(temperature_value)
		rh_value.relativeHum = round(humidity,2) #=> uncomment this to use the sensor
		relative_humidity_pub.publish(rh_value)
		loop_rate.sleep()
	
main()
