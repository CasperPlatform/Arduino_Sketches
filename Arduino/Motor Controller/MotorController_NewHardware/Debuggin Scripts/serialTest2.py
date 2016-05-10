


import serial
import time

def serialTest():

    ser = serial.Serial('/dev/cu.usbmodem621', 9600)

    hoger = bytearray()
    vanster = bytearray()
    fram = bytearray()
    bak = bytearray()


    speed0 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x00,0x00,0x0d, 0x0a, 0x04])
    speed1 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x0A,0x00,0x0d, 0x0a, 0x04])
    speed2 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x14,0x00,0x0d, 0x0a, 0x04])
    speed3 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x1E,0x00,0x0d, 0x0a, 0x04])
    speed4 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x28,0x00,0x0d, 0x0a, 0x04])
    speed5 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x32,0x00,0x0d, 0x0a, 0x04])
    speed6 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x46,0x00,0x0d, 0x0a, 0x04])
    speed7 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x50,0x00,0x0d, 0x0a, 0x04])
    speed8 = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x5A,0x00,0x0d, 0x0a, 0x04])

    time.sleep(2)

    while True:

        time.sleep(0.1)
        ser.write(speed0)
        time.sleep(0.1)
        ser.write(speed1)
        time.sleep(0.1)
        ser.write(speed2)
        time.sleep(0.1)
        ser.write(speed3)
        time.sleep(0.1)
        ser.write(speed4)
        time.sleep(0.1)
        ser.write(speed5)
        time.sleep(0.1)
        ser.write(speed6)
        time.sleep(0.1)
        ser.write(speed7)
        time.sleep(0.1)
        ser.write(speed8)
        time.sleep(0.1)
        ser.write(speed0)
        time.sleep(1)




if __name__ == '__main__':
    serialTest()
