#include "lorawan/PayloadEncoder.h"

size_t PayloadEncoder::encode(const SensorData &data, uint8_t *out, size_t capacity)
{
    // Compact example payload: signed temperature and unsigned RH,
    // both big-endian, each scaled by 100. Total: 4 bytes.
    if (capacity < 4)
        return 0;
    out[0] = static_cast<uint8_t>((data.temperatureCentiC >> 8) & 0xFF);
    out[1] = static_cast<uint8_t>(data.temperatureCentiC & 0xFF);
    out[2] = static_cast<uint8_t>((data.relativeHumidityCentiPct >> 8) & 0xFF);
    out[3] = static_cast<uint8_t>(data.relativeHumidityCentiPct & 0xFF);
    return 4;
}
