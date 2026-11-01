#pragma once
#include "interfaces/ISensor.h"

class SensorManager final : public ISensor {
public:
    bool begin() override;
    bool read(SensorData& result) override;
};
