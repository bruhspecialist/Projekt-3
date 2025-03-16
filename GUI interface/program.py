import customtkinter

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
