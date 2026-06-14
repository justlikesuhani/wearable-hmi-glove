"""
GAMING GLOVE - PC Key Press Script
====================================
Run this on your laptop while Arduino is connected via USB.
This reads gesture commands from Arduino over Serial and
presses the actual keyboard keys on your PC.

Requirements:
    pip install pyserial pyautogui

Usage:
    1. Upload gaming_glove.ino to Arduino Uno
    2. Connect Arduino to laptop via USB
    3. Run: python key_press.py
    4. Open Subway Surfers (or any game) and play!

Controls:
    Tilt FORWARD  → UP Arrow   (Jump)
    Tilt BACKWARD → DOWN Arrow (Duck/Roll)
    Tilt LEFT     → LEFT Arrow (Move Left)
    Tilt RIGHT    → RIGHT Arrow(Move Right)
"""

import serial
import pyautogui
import time
import sys

# ── CONFIG ──────────────────────────────────────────
# Change this to your Arduino's COM port
# Windows: "COM3" or "COM4" etc (check Device Manager)
# Mac/Linux: "/dev/ttyUSB0" or "/dev/ttyACM0"
PORT = "COM3"
BAUD = 9600
# ────────────────────────────────────────────────────

# Map gesture commands to keyboard keys
GESTURE_MAP = {
    "UP":    "up",
    "DOWN":  "down",
    "LEFT":  "left",
    "RIGHT": "right"
}

def main():
    print("=" * 45)
    print("  WEARABLE GAMING GLOVE — Key Controller")
    print("=" * 45)
    print(f"Connecting to Arduino on {PORT}...")

    try:
        arduino = serial.Serial(PORT, BAUD, timeout=1)
        time.sleep(2)  # Wait for Arduino to reset
        print("Connected! Wear the glove and start playing.")
        print("Press Ctrl+C to stop.\n")
    except serial.SerialException:
        print(f"\nERROR: Could not connect to {PORT}")
        print("Check your COM port in Device Manager.")
        sys.exit(1)

    # Small delay so you can switch to the game window
    print("Starting in 3 seconds — switch to your game!")
    time.sleep(3)

    pyautogui.PAUSE = 0.05  # Small delay between key presses

    while True:
        try:
            if arduino.in_waiting > 0:
                raw = arduino.readline().decode("utf-8").strip()

                if raw in GESTURE_MAP:
                    key = GESTURE_MAP[raw]
                    pyautogui.press(key)
                    print(f"Gesture: {raw:6s} → Key: {key}")

        except KeyboardInterrupt:
            print("\nStopped. Glove disconnected.")
            arduino.close()
            break
        except Exception as e:
            print(f"Error: {e}")
            break

if __name__ == "__main__":
    main()
