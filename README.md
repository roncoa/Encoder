# Encoder
EC11 Encoder Library for Arduino

## Overview
A highly optimized library for managing EC11-type and similar rotary encoders.

## Features
* Precise count management for EC11 encoders (4 pulses per detent)
* Configurable software debouncing
* Configurable pulse divider (1,2,4)
* Direction detection
* Rotation speed calculation
* Configurable position limits
* Diagnostics and debugging capabilities

## Basic Usage
```cpp
Encoder enc(pinA, pinB);           // Create encoder on specified pins
enc.setDivisor(4);                 // EC11: counts 1,2,3,4...
enc.setDivisor(2);                 // EC11: counts 2,4,6,8...
enc.setDivisor(1);                 // EC11: counts 4,8,12,16...
```

## Advanced Features
```cpp
enc.setDebounceTime(5);            // Set debounce to 5ms
enc.setLimits(-100, 100);          // Set position limits
enc.setPosition(0);                // Set current position
enc.getDirection();                // Get direction (-1,0,1)
enc.getSpeed();                    // Get rotation speed
enc.getErrorCount();               // Get sequence error count
enc.enableDebug(true);             // Enable serial debugging
```

## Complete Example
```cpp
Encoder enc(2, 3);                 // Create encoder on pins 2,3
enc.setDivisor(4);                 // Configure for EC11
enc.setDebounceTime(5);            // Set 5ms debounce
enc.setLimits(0, 100);            // Limit between 0 and 100
int32_t pos = enc.read();          // Read position


