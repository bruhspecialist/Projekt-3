import serial
import time

ser = serial.Serial('/dev/serial0', 57600, timeout=1)  # Open serial port with baudrate 57600
ser.flush()

#function to send data to the PSoC
def sendCommand(text):
    try:
        ser.write(text.encode())  # Send string command
        print("Sent: ", text)
    except Exception as e:
        print("UART Error:", e)

    return False