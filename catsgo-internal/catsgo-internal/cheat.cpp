#include <iostream>
#include <Windows.h>
#include "pch.h"
#include "utils.hpp"
#include "cheat.hpp"
#include <thread>

namespace Cheat
{
    const void banner()
    {
        std::cout << "          |\\---/|" << "\n";
        std::cout << "          | " << Global::red << "o" << Global::white << "_" << Global::red << "o" << Global::white << " | " << "\n";
        std::cout << "           \\_^_/ " << "\n";
        std::cout << R"(
     Panic key -> END

)";
    }

    const void menu()
    {
        system("cls");
        banner();

        std::cout << " [F1]  | Radar ";
        Global::radar ? std::cout << "         [" << Global::green << "ON" << Global::white << "]\n" : std::cout << "         [" << Global::red << "OFF" << Global::white << "]\n";

        std::cout << " [F2]  | Enemy Glow ";
        Global::eGlow ? std::cout << "    [" << Global::green << "ON" << Global::white << "]\n" : std::cout << "    [" << Global::red << "OFF" << Global::white << "]\n";

        std::cout << " [F3]  | Team Glow ";
        Global::tGlow ? std::cout  << "     [" << Global::green << "ON" << Global::white << "]\n" : std::cout << "     [" << Global::red << "OFF" << Global::white << "]\n";

        std::cout << " [F4]  | Third Person ";
        Global::thirdPerson ? std::cout << "  [" << Global::green << "ON" << Global::white << "]\n" : std::cout << "  [" << Global::red << "OFF" << Global::white << "]\n";

        std::cout << " [F5]  | Anti Flash ";
        Global::antiFlash ? std::cout << "    [" << Global::green << "ON" << Global::white << "]\n" : std::cout << "    [" << Global::red << "OFF" << Global::white << "]\n";

        std::cout << " [F6]  | TriggerBot ";
        Global::triggerBot ? std::cout << "    [" << Global::green << "ON" << Global::white << "]\n\n" : std::cout << "    [" << Global::red << "OFF" << Global::white << "]\n\n";

        std::cout << " [F7]  | Reset FOV\n";
        std::cout << " [+/-] | FOV Value [" << Global::fovValue << "]\n";
    }

    const uintptr_t inGame(const uintptr_t client)
    {
        const uintptr_t localPlayer = Helper::getLocalPlayer(client);
        return localPlayer;
    }

    const void radar(const uintptr_t client)
    {
        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            const uintptr_t localPlayer = Helper::getLocalPlayer(client);

            if (GetAsyncKeyState(VK_F1) & 1)
            {
                Global::radar = !Global::radar;
                menu();
            }

            if (!Global::radar)
                continue;

            if (!inGame(client))
                continue;

            for (size_t i = 0; i < 30; i++)
            {
                const uintptr_t entity = *reinterpret_cast<uintptr_t*>(client + Offset::dwEntityList + i * 0x10);

                if (!entity)
                    continue;

                *reinterpret_cast<bool*>(entity + Offset::m_bSpotted) = true;
            }
        }
    }

    const void eGlow(const uintptr_t client)
    {
        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            const uintptr_t localPlayer = Helper::getLocalPlayer(client);

            if (GetAsyncKeyState(VK_F2) & 1)
            {
                Global::eGlow = !Global::eGlow;
                menu();
            }

            if (!Global::eGlow)
                continue;

            if (!inGame(client))
                continue;

            const uintptr_t glowObjectManager = *reinterpret_cast<uintptr_t*>(client + Offset::dwGlowObjectManager);
            const int localTeam = *reinterpret_cast<int*>(localPlayer + Offset::m_iTeamNum);


            for (size_t i = 0; i < 30; i++)
            {
                const uintptr_t entity = *reinterpret_cast<uintptr_t*>(client + Offset::dwEntityList + i * 0x10);

                if (!entity)
                    continue;

                const int team = *reinterpret_cast<int*>(entity + Offset::m_iTeamNum);

                if (team == localTeam)
                    continue;

                const int lifeState = *reinterpret_cast<int*>(entity + Offset::m_lifeState);

                if (lifeState != 0)
                    continue;

                if (Global::eGlow)
                {
                    const int glowIndex = *reinterpret_cast<int*>(entity + Offset::m_iGlowIndex);

                    *reinterpret_cast<Color*>(glowObjectManager + (glowIndex * 0x38) + 0x8) = Color(1, 0, 0, 1);

                    *reinterpret_cast<bool*>(glowObjectManager + (glowIndex * 0x38) + 0x28) = true;
                    *reinterpret_cast<bool*>(glowObjectManager + (glowIndex * 0x38) + 0x29) = false;
                }
            }
        }
    }

    const void tGlow(const uintptr_t client)
    {
        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            const uintptr_t localPlayer = Helper::getLocalPlayer(client);

            if (GetAsyncKeyState(VK_F3) & 1)
            {
                Global::tGlow = !Global::tGlow;
                menu();
            }

            if (!Global::tGlow)
                continue;

            if (!inGame(client))
                continue;

            const uintptr_t glowObjectManager = *reinterpret_cast<uintptr_t*>(client + Offset::dwGlowObjectManager);
            const int localTeam = *reinterpret_cast<int*>(localPlayer + Offset::m_iTeamNum);


            for (size_t i = 0; i < 30; i++)
            {
                const uintptr_t entity = *reinterpret_cast<uintptr_t*>(client + Offset::dwEntityList + i * 0x10);

                if (!entity)
                    continue;

                const int team = *reinterpret_cast<int*>(entity + Offset::m_iTeamNum);

                if (team != localTeam)
                    continue;

                const int lifeState = *reinterpret_cast<int*>(entity + Offset::m_lifeState);

                if (lifeState != 0)
                    continue;

                if (Global::tGlow)
                {
                    const int glowIndex = *reinterpret_cast<int*>(entity + Offset::m_iGlowIndex);

                    *reinterpret_cast<Color*>(glowObjectManager + (glowIndex * 0x38) + 0x8) = Color(0, 1, 0, 1);

                    *reinterpret_cast<bool*>(glowObjectManager + (glowIndex * 0x38) + 0x28) = true;
                    *reinterpret_cast<bool*>(glowObjectManager + (glowIndex * 0x38) + 0x29) = false;
                }
            }
        }
    }

    const void thirdPerson(const uintptr_t client)
    {
        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            const uintptr_t localPlayer = Helper::getLocalPlayer(client);

            if (GetAsyncKeyState(VK_F4) & 1)
            {
                Global::thirdPerson = !Global::thirdPerson;
                menu();
            }

            if (!Global::thirdPerson)
                continue;

            if (!inGame(client))
                continue;

            *reinterpret_cast<int*>(localPlayer + Offset::m_iObserverMode) = 1;
        }
    }

    const void flash(const uintptr_t client)
    {
        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            const uintptr_t localPlayer = Helper::getLocalPlayer(client);

            if (GetAsyncKeyState(VK_F5) & 1)
            {
                Global::antiFlash = !Global::antiFlash;
                menu();
            }

            if (!Global::antiFlash)
                continue;

            if (!inGame(client))
                continue;

            *reinterpret_cast<uintptr_t*>(localPlayer + Offset::m_flFlashDuration) = 0;
        }
    }

    const void triggerBot(const uintptr_t client)
    {
        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            if (GetAsyncKeyState(VK_F6) & 1)
            {
                Global::triggerBot = !Global::triggerBot;
                menu();
            }

            if (!Global::triggerBot)
                continue;

            if (!inGame(client))
                continue;

            const uintptr_t localPlayer = Helper::getLocalPlayer(client);
            const uintptr_t crosshairId = *reinterpret_cast<uintptr_t*>(localPlayer + Offset::m_iCrosshairId);
            const uintptr_t entity = *reinterpret_cast<uintptr_t*>(client + Offset::dwEntityList + (crosshairId - 1) * 0x10);
            const uintptr_t localTeam = *reinterpret_cast<uintptr_t*>(localPlayer + Offset::m_iTeamNum);
            const uintptr_t entityTeam = *reinterpret_cast<uintptr_t*>(entity + Offset::m_iTeamNum);

            if (!crosshairId || crosshairId > 32)
                continue;

            if (localTeam == entityTeam)
                continue;

            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            Sleep(5);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
    }

    const void fov(const uintptr_t client)
    {
        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            const uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>(client + Offset::dwLocalPlayer);

            if (!inGame(client))
                continue;

            if (GetAsyncKeyState(VK_F7) & 1)
            {
                Global::fovValue = 90;
                menu();
            }

            if (GetAsyncKeyState(VK_OEM_PLUS) & 1)
            {
                Global::fovValue == 160 ? Global::fovValue = Global::fovValue : Global::fovValue += 2;
                menu();
            }

            if (GetAsyncKeyState(VK_OEM_MINUS) & 1)
            {
                Global::fovValue == 20 ? Global::fovValue = Global::fovValue : Global::fovValue -= 2;
                menu();
            }

            *reinterpret_cast<uintptr_t*>(localPlayer + Offset::m_iDefaultFOV) = Global::fovValue;
        }
    }

    const void run()
    {
        FILE* pFile = nullptr;
        AllocConsole();
        freopen_s(&pFile, "CONOUT$", "w", stdout);

        system("mode 34, 18");

        SetConsoleTitleA("CATSGO - Drxg0n");

        menu();

        const uintptr_t client = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

        // radar thread
        std::thread t1(radar, client);
        t1.detach();

        // enemy glow thread
        std::thread t2(eGlow, client);
        t2.detach();

        // team glow thread
        std::thread t3(tGlow, client);
        t3.detach();

        // third person thread
        std::thread t4(thirdPerson, client);
        t4.detach();

        // flash thread
        std::thread t5(flash, client);
        t5.detach();

        // triggerbot thread
        std::thread t6(triggerBot, client);
        t6.detach();

        // fov thread
        std::thread t7(fov, client);
        t7.detach();

        while (!Global::END)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            if (GetAsyncKeyState(VK_END) & 1)
            {
                Global::END = true;
                break;
            }
        }

        if (pFile)
            fclose(pFile);

        FreeConsole();
    }
}

