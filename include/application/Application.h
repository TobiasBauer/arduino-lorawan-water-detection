#pragma once
#include "provisioning/Credentials.h"
#include "sensors/SensorManager.h"
#include "lorawan/LmicAdapter.h"

class Application {
public:
    void begin();
    void update();

private:
    CredentialProvider credentialProvider_;
    SensorManager sensor_;
    LmicAdapter lorawan_{credentialProvider_};
    uint32_t lastSampleMs_ = 0;
    static constexpr uint32_t SAMPLE_INTERVAL_MS = 5UL * 60UL * 1000UL;
};
