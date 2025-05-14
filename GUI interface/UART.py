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

# button4 to work with psoc
def testbuttonlight():
    sendCommand("test1\n")  # Send string command to PSoC


# if statement. when choosing class 
def sendGlassSize(size):
    sendCommand(size + "\n")  # Send string command to PSoC




    try:
        if size == "shot":
            ser.write(b"shot\n")
            print("Sent: shot glass chosen")

        elif size == "medium":
            ser.write(b"medium\n")
            print("Sent: medium glass chosen")

        elif size == "large":
            ser.write(b"large\n")
            print("Sent: large glass chosen")

        else:
            print("error: invalid size")

    except Exception as e:
        print("UART drink Error:", e)
        return False