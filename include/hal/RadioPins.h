#pragma once
#include <lmic.h>

// Adafruit Feather M0 LoRa (RFM95/SX1276) pin map.
// DIO1 is on Feather D6 only if the board's JP1-to-JP3 solder bridge/wire
// is made. See README before attempting OTAA.
const lmic_pinmap lmic_pins = {
    .nss = 8,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 4,
    .dio = {3, 6, LMIC_UNUSED_PIN},
    .rxtx_rx_active = 0,
    .rssi_cal = 8,
    .spi_freq = 8000000,
};
