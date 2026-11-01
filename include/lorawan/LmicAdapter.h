#pragma once
#include "interfaces/ILoRaWan.h"
#include "provisioning/Credentials.h"
#include <lmic.h>

class LmicAdapter final : public ILoRaWan
{
public:
    explicit LmicAdapter(const CredentialProvider &provider);
    bool begin() override;
    void process() override;
    bool isJoined() const override;
    bool send(const SensorData &data) override;

    void handleEvent(ev_t event);

    // LMIC C callbacks need access to the provisioned OTAA credentials.
    friend void os_getArtEui(u1_t *buf);
    friend void os_getDevEui(u1_t *buf);
    friend void os_getDevKey(u1_t *buf);

private:
    const CredentialProvider &credentialsProvider_;
    OtaaCredentials credentials_{};
    bool joined_ = false;
    bool txQueued_ = false;
};

LmicAdapter *activeLmicAdapter();
