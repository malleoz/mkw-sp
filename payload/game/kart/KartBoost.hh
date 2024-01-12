#pragma once

#include <Common.hh>

#include <string.h>

namespace Kart {

class KartBoost {
    enum class FieldType : u8 {
        allMt,
        _star,
        mushroomAndBoostPanel,
        _bullet,
        trickAndZipper,
        _mega
    };

public:
    REPLACE KartBoost();
    virtual ~KartBoost() = default;

    REPLACE bool activate(FieldType type, s32 frames);
    REPLACE bool calc(bool &noBoost);

private:
    inline void reset();

    s16& getBoostFromType(FieldType type);

    s16 allMt;
    s16 _star;
    s16 mushroomAndBoostPanel;
    s16 _bullet;
    s16 trickAndZipper;
    s16 _mega;
    u16 boostType;
    s8 _12[0x14 - 0x12];
    f32 boostMultiplier;
    f32 boostAcceleration;
    f32 fovMultiplier;
    f32 boostSpeedLimit;
};
static_assert(sizeof(KartBoost) == 0x24);
} // namespace Kart