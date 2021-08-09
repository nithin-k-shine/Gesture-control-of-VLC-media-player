import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui#To mimic keyboard key pressings
import screen_brightness_control as sbc#To control screen brightness

ArduinoSerial = serial.Serial('com1',9600) #Create Serial port object called ArduinoSerial
time.sleep(2) #wait for 2 seconds for the communication to get established

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    incoming=incoming[2:-5]
    print(incoming)
    
    if incoming.isdigit():
        lint=int(incoming)
        lint=int(lint/11.6)
        sbc.set_brightness(100-lint)

    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)

    if 'Rewind' in incoming:
        pyautogui.hotkey('ctrl', 'left')  

    if 'Forward' in incoming:
        pyautogui.hotkey('ctrl', 'right') 

    if 'Vup' in incoming:
        pyautogui.hotkey('ctrl', 'down')
        

    if 'Vdown' in incoming:
        pyautogui.hotkey('ctrl', 'up')

    if 'size' in incoming:
        pyautogui.typewrite('a')

    if 'Fscreen' in incoming:
        pyautogui.typewrite('f')

    if 'Snap' in incoming:
        pyautogui.hotkey('shift', 's')

    incoming = "";
