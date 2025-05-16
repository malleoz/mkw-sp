#include "GhostFile.hh"

extern "C" {
#include <revolution.h>
}

#include <sp/kinoko/NANDReport.hh>

namespace System {

bool RawGhostFile::isValid() const {
    using namespace SP::Kinoko;

    if (signature != 0x524b4744) {
        NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid signature"));
        return false;
    }

    // ADDED: Validate the course
    if (course >= 0x20) {
        NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid course"));
        return false;
    }

    if (vehicle >= 0x24) {
        NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid vehicle"));
        return false;
    }

    if (character >= 0x30) {
        NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid character"));
        return false;
    }

    // Date checking isn't usually necessary, but we backport the original isValid
    if (year > 99) {
        NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid year"));
        return false;
    }

    if (month > 12) {
        NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid month"));
        return false;
    }

    if (day > 31) {
        NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid day"));
        return false;
    }

    if (isCompressed) {
        // Compressed size of inputs + header size
        size_t size = compressedInputSize + 0x8c;
        if (*reinterpret_cast<const u32 *>(buffer + size) != NETCalcCRC32(buffer, size)) {
            NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid CRC32 (compressed)"));
            return false;
        }
    } else {
        // Uncompressed size of ghost
        size_t size = sizeof(RawGhostFile) - sizeof(u32);
        if (*reinterpret_cast<const u32 *>(buffer + size) != NETCalcCRC32(buffer, size)) {
            NANDReport::Fail(NANDReport::SetNANDMsg("GHOST: Invalid CRC32 (uncompressed)"));
            return false;
        }
    }

    return true;
}

bool RawGhostFile::readFromNAND(const char *path) {
    NANDFileInfo fileInfo;
    if (NANDOpen(path, &fileInfo, NAND_ACCESS_READ) != NAND_RESULT_OK) {
        return false;
    }

    s32 size = NANDRead(&fileInfo, this, sizeof(RawGhostFile));
    NANDClose(&fileInfo);

    // The buffer size is only a maximum guarantee - we need a minimum guarantee too
    return size > 0x8c && static_cast<size_t>(size) <= sizeof(RawGhostFile);
}

} // namespace System
