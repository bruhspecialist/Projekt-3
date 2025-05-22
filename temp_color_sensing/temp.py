import serial
import time
import subprocess
import tkinter as tk
import threading

# Normalize 16-bit to 8-bit and convert to hex
def rgb16_to_hex(r, g, b):
    r = int(r)
    g = int(g)
    b = int(b)
    # Scale to 0–255 based on expected max
    max_val = 17999  # adjust to your actual maximum
    r8 = int((r / max_val) * 255)
    g8 = int((g / max_val) * 255)
    b8 = int((b / max_val) * 255)
    return f'#{r8:02x}{g8:02x}{b8:02x}'

# Function to run serial loop in background
def serial_loop():
    while True:
        ser.write(b'read_color_py\r\n')
        response = ser.readline().decode('utf-8', errors='ignore').strip()
        print(f"Received: {response}")

        try:
            r, g, b = map(str.strip, response.split(','))
            hex_color = rgb16_to_hex(r, g, b)

            # Update the GUI frame color
            def update_color():
                frame.config(bg=hex_color)
                win.title(f"Color: {hex_color}")

            win.after(0, update_color)
            subprocess.run(['process_color.exe', r, g, b])

        except ValueError:
            print("Invalid response format.")

        if not response:
            time.sleep(0.01)


# --- GUI SETUP ---
win = tk.Tk()
win.title("Color Viewer")
win.geometry("200x200")
frame = tk.Frame(win, width=200, height=200)
frame.pack(fill="both", expand=True)

# --- SERIAL SETUP ---
ser = serial.Serial(
    port='COM7',
    baudrate=57600,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1
)

if not ser.is_open:
    ser.open()

# Run serial reader in background thread
t = threading.Thread(target=serial_loop, daemon=True)
t.start()

# Start GUI main loop
win.mainloop()

# Cleanup on close
ser.close()