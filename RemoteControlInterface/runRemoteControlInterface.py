# 
# Interface de controle BatPod

import sys
import select
import tty
import termios
import bluetooth
import time
import  evdev
from Tkinter import *
import serial

ser = serial.Serial('/dev/rfcomm0')  # open serial port

def eventInfo(eventName, char, keysym, ctrl, shift):
    msg = "[" + char + "] " 
    if char == "8":
        msg += "Avancer Droit"
        ser.write(b'8') 
        time.sleep(0.5);
    elif char == "2":
        msg += "Reculer Droit"
        ser.write(b'2') 
        time.sleep(0.5);
    elif char == "7":
        msg += "Tourner Gauche"
        ser.write(b'7') 
        time.sleep(0.5);
    elif char == "9":
        msg += "Tourner Droite"
        ser.write(b'9') 
        time.sleep(0.5);
    elif char == "1":
        msg += "Reculer Gauche"
        ser.write(b'1') 
        time.sleep(0.5);
    elif char == "3":
        msg += "Reculer Droit"
        ser.write(b'3') 
        time.sleep(0.5);
    elif char == "5":
        msg += "Stop"
        ser.write(b'5') 
        time.sleep(0.5);

    else:
        msg += ""   

    return msg

def ignoreKey(event):
    ignoreSyms = [ "Shift_L", "Shift_R", "Control_L", "Control_R", "Caps_Lock" ]
    return (event.keysym in ignoreSyms)
    
def keyPressed(event):
    canvas = event.widget.canvas
    ctrl  = ((event.state & 0x0004) != 0)
    shift = ((event.state & 0x0001) != 0)
    if (ignoreKey(event) == False):
        canvas.data["info"] = eventInfo("keyPressed", event.char, event.keysym, ctrl, shift)
    if ((len(event.keysym) == 1) and (event.keysym.isalpha())):
        if (event.keysym not in canvas.data["pressedLetters"]):
            canvas.data["pressedLetters"].append(event.keysym)
    redrawAll(canvas)    


def redrawAll(canvas):
    canvas.delete(ALL)
    font = ("Arial", 16, "bold")
    info = canvas.data["info"]
    canvas.create_text(400, 50, text=info, font=font)

def init(canvas):
    canvas.data["info"] = "Mouvement"
    canvas.data["pressedLetters"] = [ ]
    redrawAll(canvas)

def run():

    print(ser.name)         # check which port was really used

    root = Tk()
    root.title("Controleur BatPod")
    canvas = Canvas(root, width=800, height=200)
    canvas.pack()
    root.canvas = canvas.canvas = canvas
    canvas.data = { }
    init(canvas)
    root.bind("<KeyPress>", keyPressed)
    root.mainloop()
    
    ser.close()             # close port

run()
