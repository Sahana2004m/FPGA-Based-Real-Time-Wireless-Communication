#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte address[6] = "00001";

char receivedData;

void setup()
{
    Serial.begin(9600);

    if (!radio.begin())
    {
        Serial.println("NRF Failed");
        while (1);
    }

    radio.setChannel(40); // 2440 MHz
    radio.setDataRate(RF24_1MBPS);
    radio.setAutoAck(false);
    radio.openReadingPipe(0, address);
    radio.startListening();

    Serial.println("Receiver Ready");
    Serial.println();
}

void loop()
{
    if (radio.available())
    {
        radio.read(&receivedData, sizeof(receivedData));

        if (receivedData == '0')
        {
            Serial.println("Received = 0");
        }
        else if (receivedData == '1')
        {
            Serial.println("Received = 1");
        }
        else
        {
            Serial.print("Unknown Data = ");
            Serial.println(receivedData);
        }

        delay(1000); // 1 second delay
    }
}
