import smbus2 as smbus
import time

I2C_ADR = 0x08 # I2C address of the PSoC (change it)
bus = smbus.SMBus(1) # default on rasberry pie

#function to send data to the PSoC
def sendData(value):
    try:
        bus.write_byte(I2C_ADR, value)
        print(f"sent to PSoC {value}")
    except Exception as e:
        print(f"Write Error: {e}") # if send fails

# function to read data 
def readData(value):
    try:
        data = bus.read_byte(I2C_ADR)
        print(f"read from PSoC {data}")
        
        return data
    
    except Exception as e:
        print(f"Read Error: {e}") # if read fails

        return None