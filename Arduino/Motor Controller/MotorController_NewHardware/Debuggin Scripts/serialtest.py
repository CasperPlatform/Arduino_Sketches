


import serial
import time

def serialTest():

    ser = serial.Serial('/dev/cu.usbmodem621', 9600)
    #ser = serial.Serial('/dev/cu.wchusbserial410', 9600)

    hoger = bytearray()
    vanster = bytearray()
    fram = bytearray()
    bak = bytearray()

    hoger = ''.join(chr(x) for x in [0x44,0x46,0x52,0x00,0x5A,0x0d, 0x0a, 0x04])
    vanster = ''.join(chr(x) for x in [0x44,0x46,0x4C,0x5A,0x5A,0x0d, 0x0a, 0x04])
    fram =  ''.join(chr(x) for x in [0x44,0x46,0x4C,0x5A,0x5A,0x0d, 0x0a, 0x04])
    bak =  ''.join(chr(x) for x in [0x44,0x46,0x4C,0x5A,0x5A,0x0d, 0x0a, 0x04])
    stop =  ''.join(chr(x) for x in [0x44,0x46,0x4C,0x5A,0x5A,0x0d, 0x0a, 0x04])

    time.sleep(2)

    while True:
        time.sleep(0.5)
        ser.write(vanster)


        time.sleep(0.5)

        ser.write(hoger)










if __name__ == '__main__':
    serialTest()
