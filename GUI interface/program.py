import customtkinter
import I2C_psoc as psoc
import threading
import time


# use spidev to talk SPI 


# Create main window
root = customtkinter.CTk() # creation of main application window
root.geometry("800x480")
root.attributes("-fullscreen", True)
root.title("Beer game!")
root.eval('tk::PlaceWindow . center')

#Grid layout configuration
root.columnconfigure(0, weight=1) # left
root.columnconfigure(1, weight=1) # right
root.rowconfigure((0, 1, 2, 3), weight=1) # row heights

#label right side
label_right = customtkinter.CTkLabel(root, text="size of drink:", font=("Arial", 38))
label_right.grid(row=0, column=1, padx=20, pady=20)

# label that updates. 
label_right2 = customtkinter.CTkLabel(root, text="\nnone", font=("Arial", 52))
label_right2.grid(row=1, column=1, padx=20, pady=20)

# function to update text 
def update_label(text):
    label_right2.configure(text=f"{text}")




# change all below here 
# Function to send I2C command
def send_drink_size(value):
    psoc.send_data(value)  # Send value to PSoC
    update_label(f"Sent: {value}")

# Function to continuously read PSoC data
def i2c_listener():
    while True:
        response = psoc.read_data()
        if response is not None:
            update_label(f"PSoC: {response}")
        time.sleep(1)

# Start I2C listener in a separate thread
i2c_thread = threading.Thread(target=i2c_listener, daemon=True)
i2c_thread.start()


# to here





# buttons left side
button1 = customtkinter.CTkButton(root, text="Shots glass", width=200, height=100, font=("Arial", 24), command=lambda: update_label("30mL"))
button1.grid(row=0, column=0, padx=20, pady=20)

button2 = customtkinter.CTkButton(root, text="lille størelse", width=200, height=100, font=("Arial", 24), command=lambda:  update_label("250mL"))
button2.grid(row=1, column=0, padx=20, pady=20)

button3 = customtkinter.CTkButton(root, text="normal størelse", width=200, height=100, font=("Arial", 24), command=lambda:  update_label("330mL"))
button3.grid(row=2, column=0, padx=20, pady=20)


#buttons right side bottom
button4 = customtkinter.CTkButton(root, text="Throw the dice!", width=300, height=175, font=("Arial", 24), command=lambda: update_label("Dice has\n been dropped!!"))
button4.grid(row=3, column=1, padx=20, pady=20)

# Run the app
root.mainloop()
