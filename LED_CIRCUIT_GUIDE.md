# LED Circuit Guide - Arduino Uno with Breadboard

## Components Needed

1. **Arduino Uno**
2. **Breadboard**
3. **1x LED** (any color - red, green, yellow, etc.)
4. **1x 220Ω Resistor** (Red-Red-Brown stripes) or 330Ω
5. **2x Jumper wires** (male-to-male)

---

## Understanding the LED

An LED has two legs:
- **Long leg (+)** = Anode (POSITIVE) → connects to Pin 13
- **Short leg (-)** = Cathode (NEGATIVE) → connects to GND

```
    LED
     ▲
    /█\
   / █ \
  ───┬───
     │  │
     │  └── Short leg (-) CATHODE → to GND
     │
     └───── Long leg (+) ANODE → to Pin 13 (through resistor)
```

---

## Circuit Diagram (Text Version)

```
    ARDUINO UNO                    BREADBOARD
    ┌─────────┐                    
    │         │                    ┌─────────────────────┐
    │  Pin 13 ├───── Wire ─────────┤ → Resistor → LED(+) │
    │         │      (red)         │                     │
    │         │                    │            LED(-)   │
    │     GND ├───── Wire ─────────┤ ←───────────┘       │
    │         │      (black)       └─────────────────────┘
    └─────────┘
```

---

## Step-by-Step Wiring Instructions

### Step 1: Place the LED on the Breadboard
```
Breadboard holes:
    A  B  C  D  E    F  G  H  I  J
    ○  ○  ○  ○  ○    ○  ○  ○  ○  ○  ← Row 10
    ○  ○  ○  ○  ○    ○  ○  ○  ○  ○  ← Row 11
    ○  ○  ○  ○  ○    ○  ○  ○  ○  ○  ← Row 12
    ○  ○  ●  ○  ○    ○  ○  ○  ○  ○  ← Row 13 (LED long leg here)
    ○  ○  ●  ○  ○    ○  ○  ○  ○  ○  ← Row 14 (LED short leg here)
    ○  ○  ○  ○  ○    ○  ○  ○  ○  ○  ← Row 15
```

- Insert LED **long leg (+)** into Row 13, Column C
- Insert LED **short leg (-)** into Row 14, Column C

### Step 2: Add the Resistor
```
Breadboard:
    A  B  C  D  E    F  G  H  I  J
    ○  ○  ○  ○  ○    ○  ○  ○  ○  ○  ← Row 10
    ○  ●══════●  ○    ○  ○  ○  ○  ○  ← Row 11 (Resistor: A11 to D11)
    ○  ○  ○  ○  ○    ○  ○  ○  ○  ○  ← Row 12
    ○  ○  ●  ○  ○    ○  ○  ○  ○  ○  ← Row 13 (LED + leg)
    ○  ○  ●  ○  ○    ○  ○  ○  ○  ○  ← Row 14 (LED - leg)
```

Wait, let me make it simpler - connect resistor in SAME ROW as LED long leg:

**Better approach:**
- Resistor one end: Row 13, Column A
- Resistor other end: Row 13, Column B (OR different row and wire)

Actually, the simplest way:

### SIMPLE CIRCUIT (3 Steps):

**Step 1:** Put LED on breadboard
- Long leg (+) → Row 13
- Short leg (-) → Row 14

**Step 2:** Put Resistor on breadboard
- One leg in SAME ROW as LED long leg (Row 13)
- Other leg in a different row (Row 10)

**Step 3:** Connect wires to Arduino
- Wire from Row 10 (resistor) → Arduino Pin 13
- Wire from Row 14 (LED short leg) → Arduino GND

---

## Visual Circuit Layout

```
ARDUINO UNO                         BREADBOARD
┌──────────────┐                    ══════════════════════════
│              │                         - - - - - + + + + +
│   [USB]      │                    ═══════════════════════════
│              │                    Row   A B C D E   F G H I J
│              │                    ─────────────────────────── 
│              │        RED         10   ○ ● ○ ○ ○   ○ ○ ○ ○ ○
│         13 ●├───────WIRE─────────────►│ │                    
│              │                    11   ○ ║ ○ ○ ○   ○ ○ ○ ○ ○
│              │                         ║ ║                    
│              │                    12   ○ ║ ○ ○ ○   ○ ○ ○ ○ ○
│              │                         [RESISTOR]             
│              │                    13   ○ ●═●═● ○   ○ ○ ○ ○ ○
│              │                           ↑ └──LED(+) long leg
│              │                           Resistor
│              │                    14   ○ ○ ● ○ ○   ○ ○ ○ ○ ○
│              │        BLACK              └──LED(-) short leg
│        GND ●├───────WIRE──────────────────────┘              
│              │                    ═══════════════════════════
└──────────────┘
```

---

## Ultra-Simple 3-Step Guide

### Step 1: Insert LED
Insert the LED into the breadboard:
- **Long leg (positive)** goes into hole **E13**
- **Short leg (negative)** goes into hole **E14**

### Step 2: Insert Resistor
Insert the 220Ω resistor:
- One end into hole **A13** (same row as LED positive)
- Other end into hole **A10**

### Step 3: Connect Wires to Arduino

| From Arduino | To Breadboard |
|-------------|---------------|
| **Pin 13** | Hole **B10** (same row as resistor end) |
| **GND** | Hole **A14** (same row as LED negative) |

---

## Final Checklist

✅ LED long leg (+) and resistor are in the SAME row (Row 13)
✅ Resistor other end is in a different row (Row 10)  
✅ Wire from Arduino Pin 13 connects to resistor row (Row 10)
✅ Wire from Arduino GND connects to LED short leg row (Row 14)

---

## Testing

1. Upload the code to Arduino
2. Open Serial Monitor at 9600 baud
3. Type `TEST` and press Enter
4. The LED should blink 2 times!

Other test commands:
- `ON` - Turn LED on continuously
- `OFF` - Turn LED off
- `L1` - Blink 1 time (Level 1)
- `L2` - Blink 3 times (Level 2)  
- `L3` - Blink 6 times (Level 3)

---

## Troubleshooting

**LED doesn't light up:**
1. Check LED orientation - long leg must be toward Pin 13
2. Make sure resistor is in the same row as LED long leg
3. Check wire connections are secure
4. Try a different LED (it might be burnt out)

**LED is very dim:**
- Use a smaller resistor (like 220Ω instead of 1kΩ)

**LED burnt out immediately:**
- Always use a resistor! Never connect LED directly to Pin 13

---

## Pin 13 Note

We use Pin 13 because:
1. It has a built-in LED on the Arduino board too
2. So you'll see BOTH the external LED AND the built-in LED blink together
3. This helps verify your code is working even if wiring is wrong
