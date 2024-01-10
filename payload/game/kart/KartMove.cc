#include "KartMove.hh"

#include "game/kart/KartState.hh"

namespace Kart {

bool KartMove::calcPreDrift() {
    constexpr int MAX_HOP_FRAME = 3;

    calcSlipDriftCharge();

    KartState *pState = accessors->state;

    if (pState->getHop()) {
        setDriftDirection();

        if (hopFrame < MAX_HOP_FRAME) {
            hopFrame++;
        }
    } else if (pState->getSlipdriftCharge()) {
        hopFrame = 0;
    }

    return pState->getHop() || pState->getSlipdriftCharge();
}

void KartMove::calcSlipDriftCharge() {
    KartState *pState = accessors->state;

    if (pState->getGround()) {
        return;
    }

    if (pState->getHop()) {
        return;
    }

    // We're already drifting
    if (pState->getDriftManual()) {
        return;
    }

    // Not holding a direction
    if (!(pState->getStickLeft() || pState->getStickRight())) {
        return;
    }

    // We're not drifting
    if (!pState->getDriftInput()) {
        pState->setSlipdriftCharge(false);
        return;
    }

    // Already slipdrifting
    if (pState->getSlipdriftCharge()) {
        return;
    }

    // Already started a drift
    if (hopStickX != 0) {
        return;
    }

    setDriftDirection();

    // Drift direction isn't set yet
    if (hopStickX == 0) {
        return;
    }

    pState->setSlipdriftCharge(true);

    // Wheelie cancel, if bike
    (*vt->onSlipDrift)(this);
}

void KartMove::setDriftDirection() {
    KartState *pState = accessors->state;

    // Already started a drift
    if (hopStickX != 0) {
        return;
    }

    // Set drift direction
    if (pState->getStickRight()) {
        hopStickX = -1;
    } else if (pState->getStickLeft()) {
        hopStickX = 1;
    }
}
} // namespace Kart