import serial
import time

try:
    ser = serial.Serial('/dev/serial0', 9600, timeout=1)  # Open serial port with baudrate 57600
    ser.flush()
except serial.SerialException as e:
    print("Error opening serial port:", e)
    ser = None


#function to send data to the PSoC
def sendCommand(text):
    try:         
        ser.write(text.encode())  # Send string command
    except Exception as e:
        print("UART Error:", e)

    return False

# button4 to work with psoc
def testbuttonlight():
    sendCommand("test1\n")  # Send string command to PSoC



def sendGlassSize(size):
    try:
        sendCommand(size + "\n")
        print("sent to PSoC: ", repr(size + "\n")) # debug
        timeout = 1  # seconds
        start_time = time.time()

        while time.time() - start_time < timeout:
            if ser.in_waiting > 0:
                try:
                    response = ser.readline().decode(errors="ignore").strip()
                    print("Received: ", response)
                    return response
                except Exception as e:
                    print("Decode error:", e)
                    return "decode_error"
            time.sleep(0.05)  # check every 50 ms

        print("No response received within timeout")
        return "no_response"

    except Exception as e:
        print("UART communication error:", e)
        return "serial_error"

