#!/usr/bin/env python

# fill.py
#
# Simple program, which sets one color to all of the LEDs located on the device
#
# Use example:
#
#   ./fill.py 127 63 255        Fills with color (R,G,B) = (127, 63, 255)
#   ./fill.py 0 0 0             Turns off all the leds
#   ./fill.py 255 255 255       Turns max on all the leds (maximum brightness white)
#
# Author: akowalew

import serial
import argparse

PixelCount = 48

ser = serial.Serial(port='/dev/ttyUSB0',
                    baudrate=57600,
                    parity=serial.PARITY_EVEN,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    xonxoff=serial.XOFF,
                    rtscts=True,
                    dsrdtr=True)

def isColor(value):
    return (value >= 0 and value < 256)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Fills LEDs to one color")
    parser.add_argument('red', type=int, help="Intensity of red color")
    parser.add_argument('green', type=int, help="Intensity of green color")
    parser.add_argument('blue', type=int, help="Intensity of blue color")
    args = parser.parse_args()

    [red, green, blue] = [args.red, args.green, args.blue]
    if (not isColor(red)) or (not isColor(green)) or (not isColor(blue)):
        print('Invalid color')

    buff = bytearray([red, green, blue] * PixelCount)
    bytesWritten = ser.write(buff)

