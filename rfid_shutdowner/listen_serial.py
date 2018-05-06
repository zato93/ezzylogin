#from time import sleep
import serial 
import ctypes
import sys

#ser = serial.Serial('/dev/cu.wchusbserial1420', 9600) # Establish the connectionon a specific port
ser = serial.Serial("COM4", 9600) # Establish the connection
#ser2 = serial.Serial("COM4", 9600) # Establish the connection
#counter = 32 # Below 32 everything in ASCII is gibberish
while True:
    if(ser.isOpen() == True and str(ser.readline()) == str(b'lock_pc\r\n')):
    	print('LOCK!!!!');
    	ctypes.windll.user32.LockWorkStation();
    	ser.close();
    	sys.exit();
    # if(ser2.isOpen() == True and str(ser2.readline()) == str(b'lock_pc\r\n')):
    # 	print('LOCK!!!!');
    # 	ctypes.windll.user32.LockWorkStation();
    # 	ser2.close();
    # 	sys.exit();
    #ctypes.windll.user32.LockWorkStation()

#    counter +=1
#    ser.write(str(chr(counter))) # Convert the decimal number to ASCII then send it to the Arduino
#    print ser.readline() # Read the newest output from the Arduino
#    sleep(.1) # Delay for one tenth of a second
#    if counter == 255:
#        counter = 32
