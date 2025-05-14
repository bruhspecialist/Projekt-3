import customtkinter as ctk
import UART as UART
import threading
import time



# Create main window
root = ctk.CTk() # creation of main application window
root.geometry("800x480")
root.attributes("-fullscreen", True)
root.title("Beer game!")
root.eval('tk::PlaceWindow . center')

ctk.set_appearance_mode("dark") # dark mode
ctk.set_default_color_theme("blue") # blue theme

#Grid layout configuration
root.columnconfigure(0, weight=1) # left
root.columnconfigure(1, weight=1) # right
root.rowconfigure((0, 1, 2, 3), weight=1) # row heights

root.grid_propagate(False) # prevent resizing of the window

# list of buttons to be tracked
buttons = []

# when button is pressed, check if it is already green. If not, set it to green and reset others to blue with label update
def updateWhenButtonPressed(selectedButton, text):
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
    label_right2.configure(text=f"{text}")
    #prints the button pressed to the console
    print(f"Button pressed: {selectedButton.cget('text')}")


#label right side top
label_right = ctk.CTkLabel(root, text="size of drink:", font=("Arial", 38))
label_right.grid(row=0, column=1, padx=20, pady=20)

# label that updates drink size. 
label_right2 = ctk.CTkLabel(root, text="\nnone", font=("Arial", 52))
label_right2.grid(row=1, column=1, padx=5, pady=5)



# buttons left side (shot)
button1 = ctk.CTkButton(root, text="Shots size", width=200, height=100, font=("Arial", 24), 
                        command=lambda: 
                        [
                            updateWhenButtonPressed(button1,"30mL"),
                            UART.sendGlassSize("shot")
                        ])
button1.grid(row=0, column=0, padx=10, pady=10)
buttons.append(button1)

# buttons left side (mediom)
button2 = ctk.CTkButton(root, text="Medium size", width=200, height=100, font=("Arial", 24), 
                        command=lambda:
                        [
                            updateWhenButtonPressed(button2, "250mL"),
                            UART.sendGlassSize("medium")
                        ])
button2.grid(row=1, column=0, padx=10, pady=10)
buttons.append(button2)

# buttons left side (large)
button3 = ctk.CTkButton(root, text="Large size", width=200, height=100, font=("Arial", 24), 
                        command=lambda:
                        [
                            updateWhenButtonPressed(button3, "330mL"),
                            UART.sendGlassSize("large")
                        ])
button3.grid(row=2, column=0, padx=10, pady=10)
buttons.append(button3)


#buttons right side bottom
button4 = ctk.CTkButton(root, text="Throw the dice!", width=300, height=175, font=("Arial", 24), 
                        command=lambda: 
                        [
                            updateWhenButtonPressed(button4,"Dice has\n been dropped!!"),
                            UART.testbuttonlight()
                        ])

button4.grid(row=3, column=1, padx=10, pady=10)
buttons.append(button4)







# Run the app
root.mainloop()
