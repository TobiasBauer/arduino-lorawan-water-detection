#pragma once
#include <stdint.h>

struct SensorData {
    int16_t temperatureCentiC; // 23.45 C -> 2345
    uint16_t relativeHumidityCentiPct; // 45.67% -> 4567
};
