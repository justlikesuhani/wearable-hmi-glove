[README (1).md](https://github.com/user-attachments/files/28927482/README.1.md)
# 🖐️ Gesture-Based Wearable Gaming Glove

Control games using hand tilts — no keyboard, no mouse. Just wear the glove and move your hand.

Built with **Arduino Uno + MPU6050** mounted on a glove. A Python script on the PC reads the gestures over Serial and presses actual keyboard keys in real time.

---

## Demo

> Subway Surfers played entirely with hand gestures — tilt forward to jump, tilt back to roll, tilt left/right to switch lanes.
---

## Gesture Controls

| Hand Gesture | Key Pressed | Game Action |
|---|---|---|
| Tilt Forward | ⬆️ Up Arrow | Jump |
| Tilt Backward | ⬇️ Down Arrow | Duck / Roll |
| Tilt Left | ⬅️ Left Arrow | Move Left |
| Tilt Right | ➡️ Right Arrow | Move Right |

---

## Hardware Required

| Component | Purpose |
|---|---|
| Arduino Uno | Microcontroller — reads sensor, sends data |
| MPU6050 | 6-axis IMU — measures hand tilt and acceleration |
| Glove | Wearable base to mount the sensor |
| Jumper wires | Connections |
| USB cable | Arduino ↔ Laptop connection |

### Wiring

```
MPU6050  →  Arduino Uno
VCC      →  3.3V
GND      →  GND
SDA      →  A4
SCL      →  A5
```

---

## Software Required

- Arduino IDE
- Python 3.x
- Python libraries:
```bash
pip install pyserial pyautogui
```

---

## How To Run

**Step 1 — Upload Arduino Code**
- Open `gaming_glove.ino` in Arduino IDE
- Select Board: Arduino Uno
- Select correct COM Port
- Upload

**Step 2 — Run Python Script**
- Open `key_press.py`
- Change `PORT = "COM3"` to your Arduino's port
  - Windows: Check Device Manager → Ports
  - Mac/Linux: Usually `/dev/ttyUSB0` or `/dev/ttyACM0`
- Run:
```bash
python key_press.py
```

**Step 3 — Play**
- Open Subway Surfers or any arrow-key game in your browser
- Switch to the game window (you have 3 seconds after script starts)
- Tilt your hand to control the game

---

## How It Works

```
Hand tilts
    ↓
MPU6050 reads acceleration on X, Y, Z axes
    ↓
Arduino converts raw values to angles (0–360°)
    ↓
Gesture detected based on angle thresholds
    ↓
Arduino sends "UP" / "DOWN" / "LEFT" / "RIGHT" over Serial
    ↓
Python reads Serial → presses actual keyboard key via pyautogui
    ↓
Game responds
```

The MPU6050 gives 6-axis data (3 accelerometer + 3 gyroscope). This project uses only the accelerometer for tilt detection, which is sufficient for discrete gesture recognition.

---

## Project Context

This project was built as part of my undergraduate work in Electronics at Delhi University. It explores **gesture-based Human-Machine Interaction (HMI)** — specifically how body-worn sensing can replace traditional input devices for intuitive control.

The core challenge was mapping continuous accelerometer values into discrete, debounced gesture events without false triggers — solved using angle thresholds and a runningX/runningY flag system that resets only when the hand returns to neutral position.

This work later informed my research direction in **wearable HMI systems and biosensor integration**.

---

## Author

**SUHANI CHADHA**
BSc Honours Electronics, Delhi University
Suhanichadha@gmail.com | https://www.linkedin.com/in/suhani-chadha/ | https://github.com/justlikesuhani
