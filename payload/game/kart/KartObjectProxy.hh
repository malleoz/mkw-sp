#pragma once

#include <Common.hh>

#include <string.h>

namespace Kart {

class KartState;

struct KartAccessors {
    void copy(const KartAccessors *rhs) {
        memcpy(this, rhs, sizeof(KartAccessors));
    }

    s8 _00[0x04 - 0x00];
    KartState *state;
    s8 _08[0x64 - 0x08];
};
static_assert(sizeof(KartAccessors) == 0x64);

class KartObjectProxy {
protected:
    KartAccessors *accessors;

private:
    u8 _4[0xc - 0x4];
};
static_assert(sizeof(KartObjectProxy) == 0xC);
} // namespace Kart