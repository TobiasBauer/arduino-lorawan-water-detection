#include <Arduino.h>
#include "application/Application.h"
#include "config/BoardConfig.h"

void Application::
    begin()
{
    Serial.begin(board::SERIAL_BAUD);
    pinMode(board::LED_PIN, OUTPUT);
    delay(1500);
    Serial.println(F("\nFeather M0 LoRaWAN sensor node"));

    if (!sensor_.begin())
    {
        Serial.println(F("ERROR: sensor initialization failed."));
    }

    if (!lorawan_.begin())
    {
        Serial.println(F("ERROR: LoRaWAN initialization failed."));
    }
}

void Application::update()
{
    // LMIC's runloop must be serviced frequently for accurate RX windows.
    lorawan_.process();

    const uint32_t now = millis();
    if (lorawan_.isJoined() &&
        (lastSampleMs_ == 0 || now - lastSampleMs_ >= SAMPLE_INTERVAL_MS))
    {
        SensorData sample{};
        if (sensor_.read(sample))
        {
            if (lorawan_.send(sample))
            {
                lastSampleMs_ = now;
                digitalWrite(board::LED_PIN, !digitalRead(board::LED_PIN));
                Serial.println(F("Sensor payload queued."));
            }
        }
    }
}
