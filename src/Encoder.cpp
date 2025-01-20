/**********************
  Encoder.cpp
  v 1.0.0
  by roncoa@gmail.com
  20/01/2025
***********************/

#include "Encoder.h"

Encoder::Encoder(int _pinA, int _pinB) : 
    pinA(_pinA), 
    pinB(_pinB),
    lastState(0),
    encDir(0),
    position(0),
    lastTime(0),
    debounceTime(5),
    divisor(4),
    lastDirection(0),
    minPosition(0),
    maxPosition(0),
    hasLimits(false),
    lastChangeTime(0),
    speed(0),
    errorCount(0),
    debugMode(false)
{    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    lastState = (digitalRead(pinA) << 1) | digitalRead(pinB);
}

int32_t Encoder::read() {
    unsigned long currentTime = millis();
    if(currentTime - lastTime >= debounceTime) {
        uint8_t currentState = (digitalRead(pinA) << 1) | digitalRead(pinB);
        if(currentState != lastState) {
            lastTime = currentTime;
            if(lastChangeTime > 0) {
                unsigned long timeDiff = currentTime - lastChangeTime;
                if(timeDiff > 0) {
                    speed = 1000 / timeDiff;
                }
            }
            lastChangeTime = currentTime;
            if(lastState == 0) {
                if(currentState == 1) encDir = 1;
                else if(currentState == 2) encDir = -1;
                else errorCount++;
            }
            else if(lastState == 1) {
                if(currentState == 3) encDir = 1;
                else if(currentState == 0) encDir = -1;
                else errorCount++;
            }
            else if(lastState == 2) {
                if(currentState == 0) encDir = 1;
                else if(currentState == 3) encDir = -1;
                else errorCount++;
            }
            else if(lastState == 3) {
                if(currentState == 2) encDir = 1;
                else if(currentState == 1) encDir = -1;
                else errorCount++;
            }
            if(encDir != 0) {
                if((lastState == 3 && currentState == 2 && encDir == 1) ||
                   (lastState == 3 && currentState == 1 && encDir == -1)) {
                    int32_t newPosition = position + ((encDir * 4) / divisor);
                    if(!hasLimits || (newPosition >= minPosition && newPosition <= maxPosition)) {
                        position = newPosition;
                        lastDirection = encDir;
                    }
                    if(debugMode) {
                        Serial.print(F("Dir: ")); Serial.print(encDir);
                        Serial.print(F(" Pos: ")); Serial.print(position);
                        Serial.print(F(" Spd: ")); Serial.println(speed);
                    }
                    encDir = 0;
                }
            }
            lastState = currentState;
        }
        if(currentTime - lastChangeTime > 1000) {
            speed = 0;
        }
    }
    return position;
}

void Encoder::setPosition(int32_t pos) {
    if(!hasLimits || (pos >= minPosition && pos <= maxPosition)) {
        position = pos;
    }
}

int32_t Encoder::getPosition() const {
    return position;
}

int8_t Encoder::getDirection() const {
    return lastDirection;
}

void Encoder::setDebounceTime(unsigned long time) {
    debounceTime = time;
}

unsigned long Encoder::getDebounceTime() const {
    return debounceTime;
}

void Encoder::setDivisor(int32_t div) {
    if(div > 0 && div <= 4) {
        divisor = div;
    }
}

int32_t Encoder::getDivisor() const {
    return divisor;
}

void Encoder::setLimits(int32_t min, int32_t max) {
    if(min < max) {
        minPosition = min;
        maxPosition = max;
        hasLimits = true;
        if(position < min) position = min;
        if(position > max) position = max;
    }
}

void Encoder::removeLimits() {
    hasLimits = false;
}

uint16_t Encoder::getSpeed() const {
    return speed;
}

uint32_t Encoder::getErrorCount() const {
    return errorCount;
}

void Encoder::enableDebug(bool on) {
    debugMode = on;
}

bool Encoder::isValid() const {
    return errorCount == 0;
}
