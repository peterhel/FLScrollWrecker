/*
 *  Make sure project type is windows application
 */

#define _WIN32_WINNT 0x0500
#include<windows.h>
#include<cmath>
#include <stdio.h>

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
    bool eat = false;

    if (wParam == WM_MOUSEWHEEL) {
        HWND windowHandle = WindowFromPoint(p->pt);
        char buff[255];
        DWORD_PTR res = 0;
        SendMessage(
            windowHandle,
            WM_GETTEXT,
            sizeof(buff),
            LPARAM(buff)
            
        );

        // Stop windows handling event if window text is blank
         eat = strlen(buff) == 0;
    }

    return (eat ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd) {

    // Set mouse hook
    HHOOK mouseHook = SetWindowsHookEx(
        WH_MOUSE_LL,      /* Type of hook */
        mouseHookProc,    /* Hook process */
        hInstance,        /* Instance */
        NULL);

    // Wait for user to exit
    MessageBox(NULL, (LPCWSTR)L"Press OK to close.", (LPCWSTR)L"", MB_OK);
    return 0;
}