# FPGA-Based Real-Time Wireless Communication Framework

An FPGA-based real-time wireless communication framework developed for Intelligent Transportation System (ITS) applications using the **PYNQ-Z2 FPGA board, NRF24L01 wireless transceivers, and Arduino UNO**.

## Overview

This project demonstrates real-time wireless data transmission between an FPGA-based transmitter and an Arduino-based receiver.

The transmitter uses a **PYNQ-Z2 FPGA** to read input switch data, process the information, and communicate with an **NRF24L01 wireless transceiver through SPI**.

The transmitted data is received by another NRF24L01 module connected to an **Arduino UNO**, where the received information is displayed through the Serial Monitor.

## System Architecture

```text
Input Switch
     │
     ▼
PYNQ-Z2 FPGA
     │
     ├── AXI GPIO
     │
     └── AXI SPI
           │
           ▼
      NRF24L01 TX
           │
           │  2.4 GHz Wireless
           ▼
      NRF24L01 RX
           │
           ▼
      Arduino UNO
           │
           ▼
      Serial Monitor
```

## Hardware

- PYNQ-Z2 FPGA Board
- NRF24L01 Wireless Transceiver × 2
- Arduino UNO
- Connecting wires
- Power supply

## Software and Tools

- AMD/Xilinx Vivado 2025.1
- Vitis 2025.1
- Arduino IDE
- PuTTY / UART terminal
- Embedded C

## Communication

The FPGA communicates with the NRF24L01 using the **SPI protocol**.

SPI signals used include:

- MOSI — Master Out Slave In
- MISO — Master In Slave Out
- SCK — Serial Clock
- CSN — Chip Select

The NRF24L01 modules communicate wirelessly in the **2.4 GHz ISM band**.

## Working Principle

1. The FPGA initializes the hardware peripherals.
2. AXI GPIO reads the input switch.
3. The FPGA processes the switch state.
4. AXI SPI communicates with the NRF24L01.
5. The NRF24L01 transmitter sends the data wirelessly.
6. The receiver NRF24L01 receives the wireless packet.
7. Arduino UNO processes the received data.
8. The received information is displayed on the Serial Monitor.
9. The process continues continuously.

## Project Structure

```text
├── README.md
├── docs/
├── vivado/
├── vitis/
├── arduino/
├── hardware/
├── images/
└── results/
```

## Results

The implemented system successfully demonstrated wireless transmission of the FPGA switch status to the Arduino receiver.

The received data was displayed on the Arduino Serial Monitor, validating communication between the transmitter and receiver.

## Applications

The framework can be extended for:

- Traffic monitoring
- Vehicle information exchange
- Vehicle-to-Vehicle communication
- Vehicle-to-Infrastructure communication
- Emergency alerts
- Smart transportation infrastructure

## Future Scope

Possible future extensions include:

- AI/ML-based traffic analysis
- V2V and V2I communication
- Longer-range wireless technologies such as LoRa or 5G
- Multiple sensor inputs
- Multiple communication nodes
- Data encryption and improved security


## Documentation

The complete project report and supporting paper are available in the `docs/` directory.

## License

This project is intended for academic and educational purposes.
