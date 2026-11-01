#pragma once
#include <stdint.h>

struct OtaaCredentials {
    uint8_t joinEui[8];
    uint8_t devEui[8];
    uint8_t appKey[16];
};

class CredentialProvider {
public:
    bool load(OtaaCredentials& out) const;
};
