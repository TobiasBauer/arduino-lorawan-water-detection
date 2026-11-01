#pragma once
#include <stddef.h>
#include <stdint.h>
#include "domain/SensorData.h"

class PayloadEncoder {
public:
    static size_t encode(const SensorData& data, uint8_t* out, size_t capacity);
};
