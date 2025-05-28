import customtkinter as ctk
import UART as UART


# ##### setup of window #####

app = ctk.CTk() # creation of main application window
app.geometry("800x480") ## Waveshare 800x480
app.attributes("-fullscreen", True)
app.title("Beer game!")
app.eval('tk::PlaceWindow . center')
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("blue") #blue theme

##### Grid layout configuration of window #####

#Grid layout configuration of window
app.columnconfigure(0, weight=1) # left
app.columnconfigure(1, weight=1) # right
app.rowconfigure((0, 1, 2, 3), weight=1) # row heights
app.grid_propagate(False) # prevent resizing of the window



##### text labels #####

#text update right side top of window
textUpdateDrinkSize = ctk.CTkLabel(app, text="size of drink:", font=("Arial", 38))
textUpdateDrinkSize.grid(row=0, column=1, padx=20, pady=20)

#text update right side middle of window (main text)
primaryTextUpdate = ctk.CTkLabel(app, text="welcome to\n Likør Lotto!", font=("Arial", 52))
primaryTextUpdate.grid(row=1, column=1, padx=5, pady=5)


##### buttons 

# button left side (shot)
shotGlassButton = ctk.CTkButton(app, text="Shots size", width=200, height=100, font=("Arial", 24), 
                        command=lambda: 
                        [
                            UART.HandleGlassSize(shotGlassButton, "Shot size", "shot", primaryTextUpdate)
                        ])
shotGlassButton.grid(row=0, column=0, padx=10, pady=10)
UART.buttons.append(shotGlassButton)

# button left side (medium)
mediumGlassButton = ctk.CTkButton(app, text="Medium size", width=200, height=100, font=("Arial", 24), 
                        command=lambda:
                        [
                            UART.HandleGlassSize(mediumGlassButton, "medium size", "medium", primaryTextUpdate)
                        ])
mediumGlassButton.grid(row=1, column=0, padx=10, pady=10)
UART.buttons.append(mediumGlassButton)

# button left side (large)
largeGlassButton = ctk.CTkButton(app, text="Large size", width=200, height=100, font=("Arial", 24), 
                        command=lambda:
                        [
                            UART.HandleGlassSize(largeGlassButton, "Large size", "large", primaryTextUpdate)
                        ])
largeGlassButton.grid(row=2, column=0, padx=10, pady=10)
UART.buttons.append(largeGlassButton)


#buttons right side bottom (starting game button)
beginGameButton = ctk.CTkButton(app, text="Throw the dice!", width=300, height=175, font=("Arial", 24), 
                        command=lambda: 
                        [
                            UART.handleStartGame(beginGameButton,"start", primaryTextUpdate),
                            app.after(4000, lambda: [primaryTextUpdate.configure(text="welcome to\n Likør Lotto!"), # reset buttons to blue after 4 sec (same with text)
                                                     beginGameButton.configure(fg_color="blue")
                            ])
                        ])
beginGameButton.grid(row=3, column=1, padx=10, pady=10)
UART.buttons.append(beginGameButton)


# Run the app
app.mainloop()
