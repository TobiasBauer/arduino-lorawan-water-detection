#pragma once
#include "domain/SensorData.h"

class ISensor {
public:
    virtual ~ISensor() = default;
    virtual bool begin() = 0;
    virtual bool read(SensorData& result) = 0;
};
