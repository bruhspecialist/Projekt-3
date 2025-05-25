import serial
import time

##### Variables ####
buttons = []

##### UART communication setup ####
try:
    ser = serial.Serial('/dev/serial0', 9600, timeout=1)  # Open serial port with baudrate 57600
    ser.flush()
except serial.SerialException as e:
    print("Error opening serial port:", e)
    ser = None


##### send commands to PSoC ####
# Function send to PSoC
def sendCommand(text):
    try:         
        ser.write(text.encode())  # Send string command
    except Exception as e:
        print("UART Error:", e)

# when button is pressed turn green, reset if new button pressed
def updateWhenButtonPressed(selectedButton, text, label):
    for button in buttons:
        if button == selectedButton:
            if button.cget("fg_color") == "green":
                return
            else:
                button.configure(fg_color="green")
        else:
            #reset all to blue
            button.configure(fg_color="blue")

    # update the label
    label.configure(text=f"{text}")
    #prints the button pressed to the console
    print(f"Button pressed: {selectedButton.cget('text')}")

# err_noCup

# function to handle glass size selection
def HandleGlassSize(button, size_text, glassSize, label):

    updateWhenButtonPressed(button, size_text, label)
    glassSizeChosen = sendGlassSize(glassSize)

    print(f"DEBUG: Received from UART: {glassSizeChosen}")  
    
    # badCup = soemthing chosen on GUI but wrong size
    if glassSizeChosen == "err_badCup":
        label.configure(text="wrong glass / no cup placed \n choose new size")
    elif glassSizeChosen == "ok":
        label.configure(text=f"Glass size: {glassSize}")
    else:
        label.configure(text="timeout\nno response from PSoC")

def handleStartGame(button, size_text, label):
    updateWhenButtonPressed(button, size_text, label)
    gameStarted = startGameFunc()
    print(f"DEBUG: Received from UART: {gameStarted}")

# noCup = nothing chosen on GUI 
    if gameStarted == "err_noCup":
        label.configure(text="no glass size chosen!\n choose a size first")
    elif gameStarted == "ok":
        label.configure(text="Game started!")
    else:
        label.configure(text="timeout\nno response from PSoC")


# test function (primary button)
def startGameFunc():
    try:
        sendCommand("start\n")  # Send string command to PSoC
        print("sent to PSoC: ", repr("start\n"))  # debug
        response = timeoutFunc()
        if response:
            return response
        else:
            print("No response received within timeout")
            return "no_response"

    except Exception as e:
        print("UART communication error: ", e)
        return "serial_err"




# sending glass size to PSoC and waiting for response
def sendGlassSize(size):
    try:
        sendCommand(size + "\n")
        print("\n sent to PSoC: ", repr(size + "\n")) # debug
        response = timeoutFunc()
        if response:
            return response
        else:
            print("No response received within timeout")
            return "no_response"

    except Exception as e:
        print("UART communication error: ", e)
        return "serial_err"


# Fucction for timeout loop 

def timeoutFunc(timeout=1.0):
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
        time.sleep(0.05)  #loop runs for 1 second and checks for response every 0.05 seconds
