// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <MinHook.h>
#include <Windows.h>
#include <cstdio>
#include <cstdint>
#include <iostream>

uintptr_t Base = (uintptr_t)GetModuleHandle(NULL);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");
uintptr_t __get_AppOwner = 0x4959D0;
uintptr_t __Is_Subscribed = 0x494B70;
uintptr_t __get_SteamId = 0x497D50;
uintptr_t Init = 0x497140;

/*struct SteamID
{
    unsigned long long value;
};*/

void CreateConsole()
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
}

void init()
{
    MH_Initialize();
    CreateConsole();
    printf("Enjoy the crack by Code Red UwU");
}

DWORD(__fastcall* __get_AppOwner_o)(DWORD* method);
DWORD __stdcall __get_AppOwner_h(DWORD* method)
{
    printf("\nCalled AppOwner");
    DWORD SIG = __get_AppOwner_o(method);
    SIG = 19591495031913959UL;
    printf("\nSuccessfully Changed AppOwner");
    return SIG;
}
bool(__fastcall* __get_IsSubscribed_o)(DWORD* method);
bool __stdcall __get_IsSubscribed_h(DWORD __this,DWORD* method)
{
    printf("\nCalled IsSubscribed");
    printf("\nSuccessfully Changed IsSubscribed");
    return true;
}
DWORD(__fastcall* __get_SteamId_o)(DWORD __this, DWORD* method);
DWORD __stdcall __get_SteamId_h(DWORD __this, DWORD* method)
{
    printf("\nCalled SteamId");
    DWORD SIG = __get_SteamId_o(__this, method);
    SIG = 19591495031913959UL;
    printf("\nSuccessfully Changed SteamID");
    return SIG;
}

void(__fastcall* __Init_o)(uint32_t appid, bool asyncCallBack, DWORD* MethodInfo);
void __stdcall __Init_h(uint32_t appid, bool asyncCallBack, DWORD* MethodInfo)
{
    printf("\nCalled Init");
    appid = 480U;
    __Init_o(appid, asyncCallBack, MethodInfo);
    printf("\nSuccessfully Changed Init");
}

void main()
{
    init();
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + __get_AppOwner), &__get_AppOwner_h, (LPVOID*)&__get_AppOwner_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + __get_AppOwner));

    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + __Is_Subscribed), &__get_IsSubscribed_h, (LPVOID*)&__get_IsSubscribed_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + __Is_Subscribed));

    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + __get_SteamId), &__get_SteamId_h, (LPVOID*)&__get_SteamId_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + __get_SteamId));

    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + Init), &__Init_h, (LPVOID*)&__Init_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + Init));
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

