# 🤖 Cleaning Bot using Arduino

A smart, Arduino-powered cleaning robot that can be controlled manually or navigate autonomously with obstacle avoidance.  
Built with **HC-05 Bluetooth**, **L298N motor driver**, and an **ultrasonic sensor**, this bot demonstrates how simple components can be combined into an efficient robotic system for DIY, households, and small businesses.  

---

## ✨ Features
- 📱 **Bluetooth Control** via HC-05 module  
- 🧭 **Custom Path Cleaning** with directional commands  
- 🚦 **Automatic Mode** with real-time obstacle avoidance  
- 🔄 **Path Memory** with reverse navigation support  
- ⚡ **Dual Motor Control** using L298N driver  
- 🛠️ Easy to build and modify for DIY robotics enthusiasts  

---

## 🖥️ Hardware Components

| Component           | Description                     |
|---------------------|---------------------------------|
| Arduino UNO         | Main microcontroller            |
| HC-05 Module        | Bluetooth communication         |
| L298N Motor Driver  | Dual DC motor control           |
| 2 × DC Motors       | Drive system                    |
| Ultrasonic Sensor   | Obstacle detection              |
| Chassis + Wheels    | Physical body of the robot      |
| Power Supply        | Battery or external power       |

---

## ⚡ How It Works
- **Manual Mode**: Control the bot with commands:  
  `F` = Forward, `B` = Backward, `L` = Left, `R` = Right, `0` = Stop.  
- **Automatic Mode**: Activated with `T`. The bot uses the ultrasonic sensor to detect obstacles and avoid them.  
- **Reverse Navigation**: After a path is completed, press `X` to retrace the stored commands back to the start.  
- **Mode Switching**:  
  - `T` → Enter automatic mode  
  - `S` → Exit automatic mode (return to manual)  

---

## 📜 Code Overview
The Arduino sketch includes:
- **Serial communication** with `Serial.read()` for Bluetooth commands  
- **Motor control** using `digitalWrite()` to drive the L298N motor driver  
- **Path storage** in a `char[]` array to record and retrace movements  
- **Ultrasonic distance measurement** for obstacle detection (`pulseIn()`)  

---

## ▶️ How to Use
1. Upload the Arduino sketch (`cleaning_bot.ino`) to the Arduino UNO.  
2. Power the bot and pair the **HC-05 Bluetooth module** with your phone.  
3. Open a **Bluetooth terminal app** and send commands:  
   - `F` → Forward  
   - `B` → Backward  
   - `L` → Left  
   - `R` → Right  
   - `0` → Stop  
   - `X` → Retrace path  
   - `T` → Start automatic obstacle avoidance mode  
   - `S` → Exit automatic mode  
