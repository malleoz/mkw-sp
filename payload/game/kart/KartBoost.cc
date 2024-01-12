#include "KartBoost.hh"

extern "C" {
#include <revolution.h>
}

namespace Kart {

KartBoost::KartBoost() : boostType(0) {
    reset();
}

void KartBoost::reset() {
    allMt = 0;
    _star = 0;
    mushroomAndBoostPanel = 0;
    _bullet = 0;
    trickAndZipper = 0;
    _mega = 0;
    boostMultiplier = 1.0f;
    boostAcceleration = 1.0f;
    boostSpeedLimit = -1.0f;
}

s16 &KartBoost::getBoostFromType(FieldType type) {
    switch (type) {
    case FieldType::allMt:
        return allMt;
    case FieldType::_star:
        return _star;
    case FieldType::mushroomAndBoostPanel:
        return mushroomAndBoostPanel;
    case FieldType::_bullet:
        return _bullet;
    case FieldType::trickAndZipper:
        return trickAndZipper;
    case FieldType::_mega:
        return _mega;
    default:
        assert(false);
    }
}

bool KartBoost::activate(FieldType type, s32 frames) {
    constexpr f32 BOOST_FOV_MULTIPLIERS[6] = {0.5f, 0.75f, 1.0f, 1.0f, 0.85f, 0.6f};
    u16 flag = 1 << static_cast<int>(type);
    s16 &boost = getBoostFromType(type);

    if ((flag & boostType && boost >= frames)) {
        return false;
    }

    boost = frames;
    boostType |= flag;
    fovMultiplier = BOOST_FOV_MULTIPLIERS[static_cast<int>(type)];
    return true;
}

bool KartBoost::calc(bool &noBoost) {
    constexpr f32 BOOST_MULTIPLIERS[6] = {1.2f, 1.25f, 1.4f, 1.7f, 1.3f, 1.25f};
    constexpr f32 BOOST_ACCELERATIONS[6] = {3.0f, 5.0f, 7.0f, 10.0f, 6.0f, 3.0f};
    constexpr f32 BOOST_LIMITS[6] = {-1.0f, 105.0f, 115.0f, 145.0f, -1.0f, 95.0f};

    bool boostCleared = false; // timer has run out on this particular boost
    bool inBoost = false;

    boostMultiplier = 1.0f;
    boostAcceleration = 1.0f;
    boostSpeedLimit = -1.0f;

    for (u8 i = 0; i < 6; i++) {
        u16 flag = 1 << i;
        if ((boostType & flag) == 0) {
            continue;
        }

        boostMultiplier = BOOST_MULTIPLIERS[i];
        boostAcceleration = BOOST_ACCELERATIONS[i];
        boostSpeedLimit = BOOST_LIMITS[i];
        s16 &boost = getBoostFromType(static_cast<FieldType>(i));
        if (--boost < 1) {
            boostCleared = true;
            boostType &= ~flag;
        } else {
            inBoost = true;
        }
    }

    noBoost = boostCleared && !inBoost;

    return boostMultiplier > 1.0f || boostSpeedLimit > 0.0f;
}

} // namespace Kart