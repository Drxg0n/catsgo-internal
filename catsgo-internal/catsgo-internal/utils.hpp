#pragma once
#include <iostream>

namespace Global
{
    std::string white = "\033[1;37m";
    std::string green = "\033[1;32m";
    std::string red = "\033[1;31m";
    bool radar = false;
    bool eGlow = false;
    bool tGlow = false;
    bool thirdPerson = false;
    bool antiFlash = false;
    bool triggerBot = false;
    bool END = false;
    size_t fovValue = 90;
}

namespace Offset
{
    constexpr uintptr_t dwLocalPlayer = 0xDEA964;
    constexpr uintptr_t dwEntityList = 0x4DFFF14;
    constexpr uintptr_t m_flFlashDuration = 0x10470;
    constexpr uintptr_t m_iDefaultFOV = 0x333C;
    constexpr uintptr_t m_iTeamNum = 0xF4;
    constexpr uintptr_t m_bSpotted = 0x93D;
    constexpr uintptr_t m_iObserverMode = 0x3388;
    constexpr uintptr_t dwGlowObjectManager = 0x535A9D8;
    constexpr uintptr_t m_lifeState = 0x25F;
    constexpr uintptr_t m_iGlowIndex = 0x10488;
    constexpr uintptr_t m_iCrosshairId = 0x11838;
    constexpr uintptr_t m_iHealth = 0x100;
}

namespace Helper
{
    const uintptr_t getLocalPlayer(const uintptr_t client)
    {
        return *reinterpret_cast<uintptr_t*>(client + Offset::dwLocalPlayer);
    }
}

struct Color
{
    float r, g, b, a;
};