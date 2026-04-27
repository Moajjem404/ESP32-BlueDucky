<div align="center">
  <h1>⚡ ESP32 BlueDucky </h1>
  <p><strong>A Stealthy, Wireless Penetration Testing & Automation Tool</strong></p>
  
  <p>
    <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=flat-square&logo=espressif" alt="ESP32" />
    <img src="https://img.shields.io/badge/Language-C++-f34b7d?style=flat-square&logo=c%2B%2B" alt="C++" />
    <img src="https://img.shields.io/badge/Interface-Web%20UI-brightgreen?style=flat-square" alt="Web UI" />
  </p>
</div>

<br/>

> **Shortcuts & Payloads in your Pocket:** ESP32 BlueDucky turns a standard ESP32 into a highly advanced Bluetooth Keyboard and Mouse. Control any PC from your phone via a beautiful WiFi Web Dashboard, type live, move the mouse, or deploy powerful **Ducky Script** payloads in seconds!

---

## ✨ Features

🔥 **Advanced Web Dashboard**
A premium, dark-themed, and responsive web interface designed for both mobile and desktop. Access everything remotely without physical contact.

⌨️ **Live Keyboard & Mouse**
Type anything directly onto the target PC. Includes a built-in virtual touchpad with multi-directional scroll and mouse-click actions.

🚀 **1-Click Quick Macros**
Over 40+ built-in quick shortcuts (Open Task Manager, CMD, PowerShell, Mute/Volume controls, Snap windows, and more) ready at the press of a button.

🦆 **Ducky Script Engine**
Write, paste, and run classic Rubber Ducky scripts (`.txt` or `.ps1`) directly from the browser. Supports all major commands (`DELAY`, `STRING`, `GUI`, `ENTER`, etc.).

🔋 **100% Wireless & Stealthy**
No need to plug into the target PC's USB port (unlike traditional USB Rubber Duckies). It connects natively via Bluetooth, making it completely wireless and unnoticeable.

---

## ⚙️ How it Works
1. **ESP32 Setup:** The ESP32 is powered via a standard power bank or USB source.
2. **Target Connection:** It connects to the target PC/Laptop disguised as a standard "Bluetooth Keyboard/Mouse".
3. **Control Connection:** It broadcasts a secure WiFi network. You connect to this WiFi with your phone to access the Web Dashboard and execute commands.

---

## 📂 Included Payloads
This project includes a built-in payload library for educational testing and pranks:
- `💀 You Have Been Hacked` - Red alert ASCII art in terminal.
- `🧑‍💻 Matrix Hacker Screen` - Green raining code effect.
- `📊 System Info Grabber` - Extracts PC specs, IP, and MAC address.
- `📡 Extract WiFi Passwords` - Grabs saved WiFi profiles.
- `👻 Ghost Notepad Flood` - Types creepy messages automatically.
- `⚠️ Fake Virus Popup` - Harmless prank popup window.

---

## 🛠️ Installation Guide

Follow these simple steps to compile and flash the code to your ESP32.

### Step 1: Prepare Arduino IDE
1. Go to `File` > `Preferences`.
2. Add this to the **Additional Boards Manager URLs**:
   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Open `Tools` > `Board` > `Boards Manager`, search for **esp32**, and install it (Version 2.0.11 or later).

### Step 2: Install the Modified Library
This project uses a specifically modified library for Bluetooth functionality.
1. Download `ESP32_BLE_Combo_Keyboard_Mouse_Modified.zip` from this repository.
2. In Arduino IDE, go to `Sketch` > `Include Library` > `Add .ZIP Library...` and select the downloaded file.

### Step 3: Flash the Code
1. Make sure `index_html.h` is kept in the EXACT SAME FOLDER as your `ESP32_WiFi_BLE_HID.ino` file.
2. Open `ESP32_WiFi_BLE_HID/ESP32_WiFi_BLE_HID.ino`.
3. Connect your ESP32 board via USB.
4. Select your ESP32 board (e.g., *DOIT ESP32 DEVKIT V1*) from `Tools` > `Board`.
5. Hit the **Upload** button!

---

## 🚀 Quick Start / Usage

1. **Pairing:** Turn on your target PC's Bluetooth and pair it with `ESP32 Keyboard/Mouse`.
2. **Connect to Web UI:** On your smartphone, connect to the WiFi network:
   - **SSID:** `ShadowGlint`
   - **Password:** `12345678`
3. **Launch Dashboard:** A captive portal will pop up automatically. If not, open a browser and navigate to `http://192.168.4.1/`.
4. **Execute:** Navigate to the **🦆 DUCKY** tab, select a payload, and press **Run**!

---

## 🤝 Credits
- The core Bluetooth HID functionality is based on a modified version of the BLE Combo Keyboard/Mouse library, originally created by the legendary **[T-vK](https://github.com/T-vK)**.

---

## ⚠️ Ethical Disclaimer

> [!CAUTION]
> **For Educational and Authorized Use Only!**
> 
> This tool is developed strictly for **educational purposes, cybersecurity research, and authorized penetration testing**. 
> - You may ONLY use this device on computer systems that you own, or for which you have explicit, written permission from the owner to test.
> - Using this device to gain unauthorized access, deploy malicious payloads, or disrupt services is **illegal** and strictly prohibited.
> 
> The creator holds no responsibility for any misuse, damage, or legal consequences caused by the use of this software. By downloading and using this project, you agree to these terms. **Be responsible, be a white-hat.** 🎩

---

## 💖 Support & Follow

If you found this project helpful, cool, or interesting, please consider giving it a **Star (⭐)** on GitHub! It helps the project grow and motivates me to add more awesome features. 

**[👉 Follow Me on GitHub](https://github.com/Moajjem404)** for more cool tools, IoT projects, and updates!

<p align="center">
  <i>"With great power comes great responsibility."</i><br>
  <b>— Built with ❤️ by ShadowGlint</b>
</p>
