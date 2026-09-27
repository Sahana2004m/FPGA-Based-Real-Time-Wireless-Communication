# PYNQ-Z2 to NRF24L01 Connections

| NRF24L01 Pin | PYNQ-Z2 Connection |
|---|---|
| VCC | 3.3V |
| GND | GND |
| MOSI | SPI MOSI |
| MISO | SPI MISO |
| SCK | SPI SCK |
| CSN | SPI SS |
| CE | GPIO |

## Communication

The PYNQ-Z2 communicates with the NRF24L01 through SPI.

The SPI signals used are:

- MOSI — Master Out Slave In
- MISO — Master In Slave Out
- SCK — Serial Clock
- CSN — Chip Select

The CE signal is connected through GPIO.
