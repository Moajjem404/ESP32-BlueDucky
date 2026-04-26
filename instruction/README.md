# ESP32 BlueDucky

Welcome to the ESP32 BlueDucky project! This project turns your ESP32 into a powerful WiFi-based Web Control Dashboard that acts as a Bluetooth Keyboard and Mouse. It features a Ducky Script runner for powerful macro execution.

## 📖 Instructions & GitHub
If you ran the "Instructions & GitHub" option from the web panel, welcome!
You can find the latest updates, source code, and issues at the official repository:
**[https://github.com/Moajjem404/ESP32-BlueDucky](https://github.com/Moajjem404/ESP32-BlueDucky)**

---

## 🦆 Ducky Script Overview
Ducky Script is a simple macro scripting language originally used by the USB Rubber Ducky. Our ESP32 can execute these scripts via Bluetooth to automate tasks on the target computer.

### How to Run a Script
1. Connect your device (PC/Phone) to the ESP32's WiFi (e.g., `ESP32_Ultimate_HID`).
2. Open your web browser and go to the captive portal IP (`http://192.168.4.1` or the assigned IP).
3. Navigate to the **🦆 DUCKY** tab in the web interface.
4. You can select a pre-made script from the dropdown menu, or write your own in the text area.
5. Make sure your target computer is connected to the ESP32 via Bluetooth.
6. Click **▶ RUN SCRIPT**.

---

### Basic Commands
Here are the commands you can use in your scripts:

* `STRING <text>`: Types the specified text exactly as written.
* `ENTER`: Presses the Enter key.
* `DELAY <time>`: Pauses execution for the specified time in milliseconds (e.g., `DELAY 500` is half a second).
* `GUI <key>`: Presses the Windows key (or Command on Mac) along with the specified key. (e.g., `GUI r` opens the Run dialog).
* `SHIFT <key>`: Presses Shift + key.
* `CTRL <key>`: Presses Ctrl + key.
* `ALT <key>`: Presses Alt + key.
* `UP`, `DOWN`, `LEFT`, `RIGHT`: Arrow keys.
* `TAB`: Presses Tab.
* `SPACE`: Presses Space.
* `ESC`: Presses Escape.
* `BACKSPACE`: Presses Backspace.
* `DELETE`: Presses Delete.

---

### 🌟 Powerful Example Scripts
You can copy and paste these into the Ducky Script editor to automate various tasks!

#### 1. Quick Note Typing
Opens notepad and types a custom message automatically.
```text
DELAY 500
GUI r
DELAY 200
STRING notepad
ENTER
DELAY 500
STRING Hello! This is an automated message.
ENTER
STRING ESP32 BlueDucky is working perfectly!
```

#### 2. Export WiFi Profiles (Windows)
Opens PowerShell and lists all saved WiFi profiles on the target computer.
```text
DELAY 500
GUI r
DELAY 200
STRING powershell
ENTER
DELAY 1000
STRING netsh wlan show profile
ENTER
```

#### 3. Quick System Lock
Locks the user's computer immediately. Great for quickly securing your device.
```text
DELAY 200
GUI l
```

#### 4. Open Specific Website
Opens Google Chrome and navigates to the project GitHub repository.
```text
DELAY 500
GUI r
DELAY 200
STRING chrome https://github.com/Moajjem404/ESP32-BlueDucky
ENTER
```

#### 5. Rickroll Terminal
Opens a terminal and plays an ASCII Rickroll. A classic prank!
```text
DELAY 500
GUI r
DELAY 200
STRING powershell
ENTER
DELAY 1000
STRING curl ascii.live/rick
ENTER
```

#### 6. Minimize All Windows (Show Desktop)
Quickly hides all open windows and shows the desktop.
```text
DELAY 200
GUI d
```

#### 7. Open YouTube
```text
DELAY 500
GUI r
DELAY 200
STRING chrome youtube.com
ENTER
```

---

### ⚠️ Safety & Ethics
Please use this tool responsibly and only on devices you own or have explicit permission to test on. This tool is built for educational purposes, IT administration, and automation.
