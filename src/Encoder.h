/**********************
  Encoder.h
  v 1.0.0
  by roncoa@gmail.com
  20/01/2025
***********************

 * EC11 Encoder Library
 * by roncoa@gmail.com
 * Libreria ottimizzata per gestire encoder rotativi di tipo EC11 e similari
 * 
 * Caratteristiche:
 * - Gestione precisa del conteggio per encoder EC11 (4 impulsi per scatto)
 * - Debounce software configurabile
 * - Divisore impulsi configurabile (1,2,4)
 * - Rilevamento direzione
 * - Calcolo velocità di rotazione
 * - Limiti di posizione impostabili
 * - Diagnostica e debug
 * 
 * Utilizzo base:
 * Encoder enc(pinA, pinB);           // Crea un encoder sui pin specificati
 * enc.setDivisor(4);                 // EC11: conta 1,2,3,4...
 * enc.setDivisor(2);                 // EC11: conta 2,4,6,8...
 * enc.setDivisor(1);                 // EC11: conta 4,8,12,16...
 * 
 * Funzionalità avanzate:
 * enc.setDebounceTime(5);            // Imposta debounce a 5ms
 * enc.setLimits(-100, 100);          // Imposta limiti di posizione
 * enc.setPosition(0);                // Imposta posizione corrente
 * enc.getDirection();                // Ottieni direzione (-1,0,1)
 * enc.getSpeed();                    // Ottieni velocità rotazione
 * enc.getErrorCount();               // Conteggio errori sequenza
 * enc.enableDebug(true);             // Abilita debug seriale
 * 
 * Esempio:
 * Encoder enc(2, 3);                 // Crea encoder su pin 2,3
 * enc.setDivisor(4);                 // Imposta per EC11
 * enc.setDebounceTime(5);            // Debounce 5ms
 * enc.setLimits(0, 100);             // Limita tra 0 e 100
 * int32_t pos = enc.read();          // Leggi posizione
 * 
 */

 
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
