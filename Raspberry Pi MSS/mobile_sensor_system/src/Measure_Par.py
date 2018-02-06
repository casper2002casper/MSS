#!/usr/bin/env python

# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# ADS1100
# This code is designed to work with the ADS1100_I2CADC I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1100_I2CADC#tabs-0-product_tabset-2

# ADS1100 address, 0x48(72)
# Read data back from 0x00(00), 2 bytes
# raw_adc MSB, raw_adc LSB
#to start a single cconversion, write a one into bit 7(ST/BSY) and set bit 4 (SC) to 1
#bit 5 and 6 are reserved bits
#Bit 3-2 (DR1 and DR0) control the datarate, lowest value is the fastest
#DR1	DR0	datarate
#0	0	128SPS
#0	1	32SPS
#1	0	16SPS
#1	1	8SPS

#Bits (PGA) 1 and 0 control the gain
#PGA 1	PGA 0	Gain
#0	0	1
#0	1	2
#1	0	4
#1	1	8

#command 0x00 starts fastest continuous conversion.
#command 0x9C starts slowest single conversion
#data = bus.read_i2c_block_data(0x48, 0x00, 2)

import smbus
import time
import rospy
from mobile_sensor_system.msg import par
import time
RATE = 0.5

#------------------main----------------
def main():
	rospy.init_node("Measure_PAR_Node", anonymous=True)
	par_pub = rospy.Publisher("par", par, queue_size=1000)	
	loop_rate = rospy.Rate(RATE)
	# Get I2C bus
	bus = smbus.SMBus(1)
	time.sleep(0.5)
	par_value = par()

	while not rospy.is_shutdown():	
		time.sleep(0.2)
		data = bus.read_i2c_block_data(0x48, 0x9C, 2)
		# Convert the data
		raw_adc = data[0] * 256 + data[1]
		if raw_adc > 32767 :
			raw_adc -= 65536

		value = (float(raw_adc) * 5  /(32768))
		# Output data to screen
		#print "Digital Value of Analog Input : %d " %raw_adc
		#print "Data0 = " data[0]
		#print "Data1 = " data[1]
		#print "output in volts is: %.4f" %value
		PAR = value *500
		#print "output in umol/m^2/s^2 = %.4f" %PAR

		par_value.par = round(PAR,1)
		par_pub.publish(par_value)
		loop_rate.sleep()
	
main()
	
