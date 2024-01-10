#pragma once

#include "game/kart/KartObjectProxy.hh"

namespace Kart {

class KartMove : KartObjectProxy {
public:
    REPLACE bool calcPreDrift();

private:
    struct vtable {
        u8 _00[0x34 - 0x00];
        void (*onSlipDrift)(KartMove *self);
        u8 _38[0x64 - 0x38];
    };
    static_assert(sizeof(vtable) == 0x64);

    void calcSlipDriftCharge();
    void setDriftDirection();

    vtable *vt;
    u8 _010[0x0cc - 0x010];
    s32 hopStickX;
    s32 hopFrame;
    u8 _0d4[0x2c4 - 0x0d4];
};
static_assert(sizeof(KartMove) == 0x2C4);
} // namespace Kart