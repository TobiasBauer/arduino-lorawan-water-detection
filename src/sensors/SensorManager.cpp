#include <Arduino.h>
#include "sensors/SensorManager.h"

bool SensorManager::begin()
{
    // Initialize actual sensor drivers here (I2C/SPI/GPIO).
    // This starter returns demonstration values until a sensor is selected.
    return true;
}

bool SensorManager::read(SensorData &result)
{
    // Replace with real sensor readings.
    result.temperatureCentiC = 2150;        // 21.50 C demonstration value
    result.relativeHumidityCentiPct = 5030; // 50.30% demonstration value
    return true;
}
