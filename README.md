# 🚀 plateFlipper

Controlling money outside my wallet because the state takes photos of my motorcycle without permission and charges me for it.  
[![diagram](https://github.com/maagmirror/plateFlipper/blob/main/diagram.jpg?raw=true)](https://github.com/maagmirror/plateFlipper/blob/main/diagram.jpg?raw=true)

---

## 🛠️ **Required Components**

✔️ **Arduino UNO / Arduino NANO** → x1  
✔️ **Servo (15kg or more)** → x1  
✔️ **Arduino cables** → x1 kit  
✔️ **Push button** → x1  
💡 _(Optional)_ **SC2272-M4 wireless module** → x1  
→ This allows you to activate the servo **remotely**, but if you just want to use the button, simply **enjoy**.  
[![flipper](https://github.com/maagmirror/plateFlipper/blob/main/flipper.gif?raw=true)](https://github.com/maagmirror/plateFlipper/blob/main/flipper.gif?raw=true)

---

## ⚡ **Features and Improvements**

✔️ **Improved button debouncing** → The system ignores false triggers or electrical noise.  
✔️ **Last position saved in EEPROM** → When restarting, the servo automatically returns to its last position.  
✔️ **EEPROM protection** → Prevents unnecessary writes for increased durability.  
✔️ **Precise button detection** → Only activates when actually pressed and released.  
✔️ **Smooth servo movement** _(optional)_ → Prevents jerky movements when restarting.  
✔️ **Indicator LED** → Reflects the current servo state.  
✔️ **No flicker on startup** → LED no longer flickers when Arduino boots.

---

## 🎮 **How Does It Work?**

1️⃣ **Press the button** → The servo rotates **110°** and activates the system.  
2️⃣ **Press again** → The servo returns to **0°** and deactivates the system.  
3️⃣ **Trouble-free restart** → If you turn off the Arduino, the servo remembers its last position.  
4️⃣ **(Optional) Use the remote control** → If you have the SC2272-M4 module, you can activate it wirelessly.

---

## 📌 **How to Install?**

1️⃣ **Upload the code to your Arduino** using the Arduino IDE.  
2️⃣ **Connect the servo and button** according to the diagram.  
3️⃣ _(Optional)_ If using the wireless module, connect it properly.  
4️⃣ **Ready to use! 🚀**

---

💡 **If you have questions or improvements, contribute to the project!** 😃
