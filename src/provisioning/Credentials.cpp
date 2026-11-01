#include "provisioning/Credentials.h"
#include <Arduino.h>
#include <cstring>
#include "credentials.h"

bool CredentialProvider::load(OtaaCredentials &out) const
{
    memcpy(out.joinEui, JOIN_EUI, sizeof(out.joinEui));
    memcpy(out.devEui, DEV_EUI, sizeof(out.devEui));
    memcpy(out.appKey, APP_KEY, sizeof(out.appKey));

    // Fail fast on untouched example credentials.
    bool allZero = true;
    for (uint8_t b : out.devEui)
        allZero &= (b == 0);
    for (uint8_t b : out.appKey)
        allZero &= (b == 0);
    return !allZero;
}
