# Inbyggda-system-Labb-3

## Labben går ut på att dels använda ADC-enheten på Arduinon för att läsa av en potentiometer, en digitalingång för att läsa av en knapp, och dels använda timer/compare-enheter för att takta systemet. 

Koden är skriven för en sheild tillverkad i en tidigare kurs, med undantag för en extern knapp kopplad på Arduinons Digital Pin 2 för att nå interrupt funktionen.
Knappen är kopplad med ett pulldown-motstånd på 10K Ohm

```
                 __*__
    D2-----------|   |-----5V
    GND--10KOhm--|   |
```
På Sheilden:
En potentiometer är kopplad till A0 på Arduinon

```
              A0
              | 
    GND-----^^^^-----5V
           10K Ohm
```

En LED är kopplad till Digital Pin 11

```
               \\
    D11--330---|<-----5V
```