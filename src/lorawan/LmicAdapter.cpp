#include <Arduino.h>
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <cstring>

#include "lorawan/LmicAdapter.h"
#include "lorawan/PayloadEncoder.h"
#include "hal/RadioPins.h"

static LmicAdapter *g_instance = nullptr;

LmicAdapter *activeLmicAdapter() { return g_instance; }

// LMIC calls these C-style callbacks during OTAA.
void os_getArtEui(u1_t *buf)
{
    if (g_instance)
        memcpy(buf, g_instance->credentials_.joinEui, 8);
}
void os_getDevEui(u1_t *buf)
{
    if (g_instance)
        memcpy(buf, g_instance->credentials_.devEui, 8);
}
void os_getDevKey(u1_t *buf)
{
    if (g_instance)
        memcpy(buf, g_instance->credentials_.appKey, 16);
}

LmicAdapter::LmicAdapter(const CredentialProvider &provider)
    : credentialsProvider_(provider) {}

bool LmicAdapter::begin()
{
    g_instance = this;
    if (!credentialsProvider_.load(credentials_))
    {
        Serial.println(F("ERROR: OTAA credentials missing/unchanged. Copy include/credentials.h.example to include/credentials.h and configure it."));
        return false;
    }

    os_init_ex(&lmic_pins);
    LMIC_reset();
    LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100); // widen RX windows by 1%
    LMIC_setLinkCheckMode(0);
    LMIC_startJoining();
    Serial.println(F("LMIC initialized; starting OTAA join."));
    return true;
}

void LmicAdapter::process()
{
    os_runloop_once();
}

bool LmicAdapter::isJoined() const { return joined_; }

bool LmicAdapter::send(const SensorData &data)
{
    if (!joined_ || (LMIC.opmode & OP_TXRXPEND))
        return false;

    uint8_t payload[4];
    const size_t length = PayloadEncoder::encode(data, payload, sizeof(payload));
    if (length == 0)
        return false;

    // Port 1, unconfirmed uplink. Confirmed uplinks should be used sparingly.
    LMIC_setTxData2(1, payload, length, 0);
    txQueued_ = true;
    return true;
}

void onEvent(ev_t event)
{
    if (g_instance)
        g_instance->handleEvent(event);
}

void LmicAdapter::handleEvent(ev_t event)
{
    switch (event)
    {
    case EV_JOINING:
        Serial.println(F("OTAA: joining..."));
        break;
    case EV_JOINED:
        joined_ = true;
        txQueued_ = false;
        Serial.println(F("OTAA: joined TTN."));
        LMIC_setLinkCheckMode(0);
        break;
    case EV_JOIN_FAILED:
        joined_ = false;
        Serial.println(F("OTAA: join failed."));
        break;
    case EV_TXCOMPLETE:
        txQueued_ = false;
        Serial.println(F("Uplink cycle complete."));
        if (LMIC.txrxFlags & TXRX_ACK)
            Serial.println(F("Downlink ACK received."));
        if (LMIC.dataLen)
            Serial.println(F("Downlink data received."));
        break;
    case EV_TXCANCELED:
        txQueued_ = false;
        Serial.println(F("Uplink canceled."));
        break;
    default:
        break;
    }
}
