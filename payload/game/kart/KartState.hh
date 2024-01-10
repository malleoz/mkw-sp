#pragma once

#include <Common.hh>

namespace Kart {

enum class Bitfield0 : u32 {
    ACCELERATE = 0x1,
    BRAKE = 0x2,
    DRIFT_INPUT = 0x4,
    DRIFT_MANUAL = 0x8,
    BEFORE_RESPAWN = 0x10,
    WALL_3_COLLISION = 0x20,
    WALL_COLLISION = 0x40,
    HOP_START = 0x80,
    ACCELERATE_START = 0x100,
    GROUND_START = 0x200,
    VEHICLE_BODY_FLOOR_COLLISION = 0x400,
    ANY_WHEEL_COLLISION = 0x800,
    ALL_WHEELS_COLLISION = 0x1000,
    STICK_LEFT = 0x2000,
    AIRTIME_OVER_20 = 0x8000,
    STICKY_ROAD = 0x10000,
    GROUND = 0x40000,
    HOP = 0x80000,
    BOOST = 0x100000,
    AIR_START = 0x800000,
    STICK_RIGHT = 0x1000000,
    SOMETHING_EXPLOSION = 0x2000000,
    MUSHROOM_BOOST = 0x4000000,
    SLIPDRIFT_CHARGE = 0x8000000,
    DRIFT_AUTO = 0x10000000,
    WHEELIE = 0x20000000,
    JUMP_PAD = 0x40000000,
    RAMP_BOOST = 0x80000000
};

inline constexpr Bitfield0 operator&(Bitfield0 x, Bitfield0 y) {
    return static_cast<Bitfield0>(static_cast<int>(x) & static_cast<int>(y));
}

inline constexpr Bitfield0 operator|(Bitfield0 x, Bitfield0 y) {
    return static_cast<Bitfield0>(static_cast<int>(x) | static_cast<int>(y));
}

inline constexpr Bitfield0 operator~(Bitfield0 x) {
    return static_cast<Bitfield0>(~static_cast<int>(x));
}

inline constexpr Bitfield0 operator|=(Bitfield0 &x, Bitfield0 y) {
    x = x | y;
    return x;
}

inline constexpr Bitfield0 operator&=(Bitfield0 &x, Bitfield0 y) {
    x = x & y;
    return x;
}

class KartState {
public:
    void copy(const KartState *rhs) {
        memcpy(this, rhs, sizeof(KartState));
    }

    bool getGround() {
        return (bool)(bitfield0 & Bitfield0::GROUND);
    }

    bool getHop() {
        return (bool)(bitfield0 & Bitfield0::HOP);
    }

    bool getDriftManual() {
        return (bool)(bitfield0 & Bitfield0::DRIFT_MANUAL);
    }

    bool getStickLeft() {
        return (bool)(bitfield0 & Bitfield0::STICK_LEFT);
    }

    bool getStickRight() {
        return (bool)(bitfield0 & Bitfield0::STICK_RIGHT);
    }

    bool getDriftInput() {
        return (bool)(bitfield0 & Bitfield0::DRIFT_INPUT);
    }

    bool getSlipdriftCharge() {
        return (bool)(bitfield0 & Bitfield0::SLIPDRIFT_CHARGE);
    }

    void setSlipdriftCharge(bool enable) {
        if (enable) {
            bitfield0 |= Bitfield0::SLIPDRIFT_CHARGE;
        } else {
            bitfield0 &= ~Bitfield0::SLIPDRIFT_CHARGE;
        }
    }

private:
    s8 _00[0x04 - 0x00];
    Bitfield0 bitfield0;
    s8 _08[0xc0 - 0x8];
};
static_assert(sizeof(KartState) == 0xC0);
} // namespace Kart