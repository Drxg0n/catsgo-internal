#include <Windows.h>
#include "pch.h"
#include "cheat.hpp"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD reason,
    LPVOID lpvReserved
)
{
    if (reason == 1)
    {
        DisableThreadLibraryCalls(hinstDLL);
        const auto thread = CreateThread(
            nullptr,
            0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(Cheat::run),
            hinstDLL,
            0,
            nullptr
        );

        if (thread)
            CloseHandle(thread);
    }

    return 1;
}