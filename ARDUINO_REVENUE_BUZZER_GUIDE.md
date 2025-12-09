# Arduino Revenue Notification LED - Setup Guide

## Overview
This feature adds an Arduino LED that blinks when daily revenue reaches certain thresholds:

| Level | Revenue Threshold | LED Blinks |
|-------|------------------|------------|
| Level 1 | 3,000 DT | 1 blink |
| Level 2 | 10,000 DT | 3 blinks |
| Level 3 | 20,000 DT | 6 blinks |

The LED only triggers **once** per level per day (so you won't see constant blinking).

---

## Hardware Requirements

1. **Arduino Uno** (or compatible board)
2. **LED** (or use the built-in LED on Pin 13 - no external LED needed!)
3. **220 ohm resistor** (if using external LED)
4. **USB cable** (to connect Arduino to your computer)

---

## Hardware Wiring

### Option 1: Use Built-in LED (EASIEST - NO WIRING!)
Most Arduino boards have a built-in LED on **Pin 13**. Just upload the code and it works!

### Option 2: External LED
```
LED              ARDUINO
  Long leg (+) ---> Pin 13
  Short leg (-) ---> 220 ohm resistor ---> GND
```

---

## Step-by-Step Setup

### Step 1: Upload Arduino Code

1. Open **Arduino IDE** on your computer
2. Open the file: `C:\Users\hmza\Desktop\projectc++\arduino_sketch\revenue_buzzer.ino` 
3. Select your Arduino board:
   - Go to **Tools → Board → Arduino Uno**
4. Select the correct COM port:
   - Go to **Tools → Port** → Select the COM port where Arduino is connected
5. Click the **Upload** button (→ arrow icon)
6. Wait for "Done uploading" message

### Step 2: Test the Connection

1. Open **Serial Monitor** in Arduino IDE (Tools → Serial Monitor)
2. Set baud rate to **9600**
3. You should see: `Smart Optical Store - Revenue LED Ready!`
4. Type `TEST` and press Enter - you should see the LED blink 2 times

### Step 3: Run Your Qt Application

1. **Close Arduino IDE Serial Monitor** (important! Only one program can use the COM port)
2. Build and run your Qt application
3. The dashboard will automatically:
   - Connect to Arduino on startup
   - Check revenue thresholds when loading dashboard data
   - Send LED commands when thresholds are reached

---

## Testing Commands (Arduino Serial Monitor)

You can test the Arduino by sending these commands:

| Command | Action |
|---------|--------|
| `TEST` | Play 2 test beeps |
| `L1` | Simulate Level 1 (1 beep) |
| `L2` | Simulate Level 2 (3 beeps) |
| `L3` | Simulate Level 3 (6 beeps) |
| `RESET` | Reset daily levels |
| `STATUS` | Show current level |

---

## How It Works

1. When the **Dashboard** loads, it queries today's total revenue
2. If revenue >= 3000 DT and Level 1 not yet triggered → Sends `L1` command
3. If revenue >= 10000 DT and Level 2 not yet triggered → Sends `L2` command
4. If revenue >= 20000 DT and Level 3 not yet triggered → Sends `L3` command
5. Each level only triggers **once per day**

---

## Troubleshooting

### Arduino not detected
1. Check USB connection
2. Install CH340 or FTDI drivers if needed
3. Close any other programs using the COM port (like Arduino IDE Serial Monitor)

### No sound from buzzer
1. Check wiring - ensure buzzer is connected to Pin 8 and GND
2. Test with `TEST` command in Serial Monitor
3. Try reversing buzzer polarity (some buzzers are polarized)

### Buzzer beeps but Qt app doesn't trigger it
1. Make sure Arduino IDE Serial Monitor is **closed**
2. Check Qt console output for `[ARDUINO]` messages
3. Verify Arduino is detected: Look for `Arduino auto-connected successfully`

---

## Files Modified

- `arduino.h` - Added revenue notification methods
- `arduino.cpp` - Implemented checkRevenueThreshold(), sendRevenueLevel(), etc.
- `dashboardwindow.h` - Added todayRevenue member variable
- `dashboardwindow.cpp` - Added Arduino threshold checking when loading revenue

## Files Created

- `arduino_sketch/revenue_buzzer.ino` - Arduino code to upload

---

## Console Output Example

When working correctly, you'll see in Qt console:
```
========================================
Arduino object created
Revenue notification thresholds:
  Level 1: 3000 DT (1 beep)
  Level 2: 10000 DT (3 beeps)
  Level 3: 20000 DT (6 beeps)
========================================
[DASHBOARD] Auto-connecting to Arduino on startup...
CONNECTION SUCCESS!
✅ Today's Revenue: 5000.5
========================================
[ARDUINO] Checking revenue threshold...
[ARDUINO] Today's Revenue: 5000.5 DT
[ARDUINO] Last notified level: 0
[ARDUINO] Current level based on revenue: 1
[ARDUINO] 🎉 NEW LEVEL REACHED! Triggering buzzer...
[ARDUINO] 🔔 SENDING REVENUE NOTIFICATION
[ARDUINO] Level 1 (3000 DT) - 1 beep
[ARDUINO] Command: L1
[ARDUINO] ✅ Notification sent!
========================================
```
