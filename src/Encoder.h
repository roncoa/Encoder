/**********************
  Encoder.h
  v 1.0.0
  by roncoa@gmail.com
  20/01/2025
***********************/
 
#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
private:
    const int pinA;
    const int pinB;
    uint8_t lastState;
    int8_t encDir;
    int32_t position;
    unsigned long lastTime;
    unsigned long debounceTime;
    int32_t divisor;
    int8_t lastDirection;
    // Limiti di posizione
    int32_t minPosition;
    int32_t maxPosition;
    bool hasLimits;
    // Velocità
    unsigned long lastChangeTime;
    uint16_t speed;
    // Diagnostica
    uint32_t errorCount;
    bool debugMode;
    
public:
    Encoder(int _pinA, int _pinB);
    int32_t read();
    void setPosition(int32_t pos);
    int32_t getPosition() const;
    int8_t getDirection() const;
    void setDebounceTime(unsigned long time);
    unsigned long getDebounceTime() const;
    void setDivisor(int32_t div);
    int32_t getDivisor() const;
    void setLimits(int32_t min, int32_t max);
    void removeLimits();
    uint16_t getSpeed() const;    
    uint32_t getErrorCount() const;
    void enableDebug(bool on);
    bool isValid() const;
};

#endif
