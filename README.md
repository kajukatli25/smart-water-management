# Smart Water Management

A C++ OOPS mini project based on **SDG 6 (Clean Water and Sanitation)**, target 6.4 (water-use efficiency).

Built by Saloni (Enrollment No. 13414803125), 3rd Semester, Department of Information Technology,
Maharaja Agrasen Institute of Technology, Rohini, New Delhi.

## What it does

A console simulation of campus water monitoring. Two sensor classes (flow and tank level) feed a
`WaterMonitor` class that displays readings and raises alerts:

| Condition | Decision |
|---|---|
| Quiet hours, flow >= 0.5 L/min for 30+ minutes | Possible leak, with estimated volume |
| Tank level <= 20% | Low tank level |
| Tank level >= 95% | High tank level |
| Nothing triggered | Normal |

## OOP concepts used

- **Abstraction**: `Sensor` with pure virtual `read()` and `label()`
- **Encapsulation**: private readings, validated in constructors
- **Inheritance**: `FlowSensor` and `TankLevelSensor` derive from `Sensor`
- **Runtime polymorphism**: `showReading()` works on any `Sensor&`

## Build and run

```bash
g++ -std=c++17 -Wall -Wextra -pedantic SmartWater.cpp -o SmartWater
./SmartWater        # on Windows PowerShell: .\SmartWater.exe
```

The program runs four predefined test cases automatically.

## Sample output

```
Smart Water Management | SDG 6

Case 1: Normal daytime use
Flow (L/min): 2.0
Tank level (%): 60.0
Status: Normal

Case 2: Continuous flow during quiet hours
Flow (L/min): 0.5
Tank level (%): 45.0
Alert: Possible leak. Inspect the pipe.
Estimated volume (L): 15.0

Case 3: Low tank level
Flow (L/min): 0.0
Tank level (%): 15.0
Alert: Tank level is low.

Case 4: High tank level
Flow (L/min): 0.0
Tank level (%): 96.0
Alert: Tank level is high.
```

## Future scope

Read from files or real sensors, add timestamps, keep an alert history, and learn a per-building baseline.
