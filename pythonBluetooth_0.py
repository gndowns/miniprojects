#! /usr/bin/python

import serial

btSerial = serial.Serial("/dev/rfcomm0", baudrate=9600)

while(True):
  data = input("Enter 1/0: ")
  btSerial.write(str(data))
