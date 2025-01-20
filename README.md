# Encoder

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
