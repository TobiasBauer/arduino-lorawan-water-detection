#pragma once
#include "domain/SensorData.h"

class ILoRaWan {
public:
    virtual ~ILoRaWan() = default;
    virtual bool begin() = 0;
    virtual void process() = 0;
    virtual bool isJoined() const = 0;
    virtual bool send(const SensorData& data) = 0;
};
