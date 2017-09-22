#! /usr/bin/python

import serial

btSerial = serial.Serial("/dev/rfcomm0", baudrate=115200)

while(True):
  data = input("Enter 1/0: ")
  btSerial.write(str(data))
