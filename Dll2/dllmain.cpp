/*This was made using va-LOL-rant made by @pean153
* link: https://www.unknowncheats.me/forum/valorant/414174-va-lol-rant-internal-external-aimassist.html
* 
* For the basic parts of the menu I used CasualCoder91's Console Menu
* link: https://github.com/CasualCoder91/ConsoleMenu (if any of you wanna use it in your own projects ;])
* 
* Put a lot of hours into this and ran into a lot of issues this was super annoying to make, but it was also fun. Hope you enjoy :)
* 
* Have fun
*/

#pragma once

#include "pch.h"
#include "interception.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "Menu.h"
#include <Windows.h>

using namespace std;

int snapValue;

int get_screen_width(void) {
    return GetSystemMetrics(SM_CXSCREEN);
}

int get_screen_height(void) {
    return GetSystemMetrics(SM_CYSCREEN);
}

struct point {
    double x;
    double y;
    point(double x, double y) : x(x), y(y) {}
};

//to hide console cursor (doesn't work for some reason? it did before.)
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

//to avoid system()
void clear() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

//original color purple (not set to default)
inline bool is_color(int red, int green, int blue) {
   if (green >= 190) {
        return false;
    }

    if (green >= 140) {
        return abs(red - blue) <= 8 &&
            red - green >= 50 &&
            blue - green >= 50 &&
            red >= 105 &&
            blue >= 105;
    }

    return abs(red - blue) <= 13 &&
        red - green >= 60 &&
        blue - green >= 60 &&
        red >= 110 &&
        blue >= 100;
}

//red
inline bool is_colorR(int red, int green, int blue) {
    //red = bad.
    return false;
}

//yellow
inline bool is_colorY(int red, int green, int blue) {

    if (red < 160)
    {
        return false;
    }
    if (red > 161 && red < 255) {
        return green > 150 && green < 255 && blue > 0 && blue < 79;
    }
    return false;
}

InterceptionContext context;
InterceptionDevice device;
InterceptionStroke stroke;
BYTE* screenData = 0;
bool run_threads = true;
const int screen_width = get_screen_width(), screen_height = get_screen_height();

int aim_x = 0;
int aim_y = 0;

//bot with purple (original (again not default))
void bot() {
    int w = 100, h = 100;
    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();

    HDC hScreen = GetDC(NULL);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    screenData = (BYTE*)malloc(5 * screen_width * screen_height);
    HDC hDC = CreateCompatibleDC(hScreen);
    point middle_screen(screen_width / 2, screen_height / 2);

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = w;
    bmi.biHeight = -h;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;

    while (run_threads) {
        Sleep(6);
        HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
        BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, middle_screen.x - (w/2), middle_screen.y - (h/2), SRCCOPY);
        SelectObject(hDC, old_obj);
        GetDIBits(hDC, hBitmap, 0, h, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
        bool stop_loop = false;
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w * 4; i += 4) {
                #define red screenData[i + (j*w*4) + 2]
                #define green screenData[i + (j*w*4) + 1]
                #define blue screenData[i + (j*w*4) + 0]

                if (is_color(red, green, blue)) {
                    aim_x = (i / 4) - (w/2);
                    //original aim_y = j - (h / 2) + 3;
                    aim_y = j - (h/2) + snapValue;
                    stop_loop = true;
                    break;
                }
            }
            if (stop_loop) {
                break;
            }
        }
        if (!stop_loop) {
            aim_x = 0;
            aim_y = 0;
        }
    }
}

//bot with red
void botR() {
    int w = 100, h = 100;
    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();

    HDC hScreen = GetDC(NULL);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    screenData = (BYTE*)malloc(5 * screen_width * screen_height);
    HDC hDC = CreateCompatibleDC(hScreen);
    point middle_screen(screen_width / 2, screen_height / 2);

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = w;
    bmi.biHeight = -h;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;

    while (run_threads) {
        Sleep(6);
        HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
        BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, middle_screen.x - (w / 2), middle_screen.y - (h / 2), SRCCOPY);
        SelectObject(hDC, old_obj);
        GetDIBits(hDC, hBitmap, 0, h, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
        bool stop_loop = false;
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w * 4; i += 4) {
                    #define red screenData[i + (j*w*4) + 2]
                    #define green screenData[i + (j*w*4) + 1]
                    #define blue screenData[i + (j*w*4) + 0]

                if (is_colorR(red, green, blue)) {
                    aim_x = (i / 4) - (w / 2);
                    //original aim_y = j - (h / 2) + 3;
                    aim_y = j - (h / 2) + snapValue;
                    stop_loop = true;
                    break;
                }
            }
            if (stop_loop) {
                break;
            }
        }
        if (!stop_loop) {
            aim_x = 0;
            aim_y = 0;
        }
    }
}

//bot with yellow
void botY() {
    int w = 100, h = 100;
    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();

    HDC hScreen = GetDC(NULL);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    screenData = (BYTE*)malloc(5 * screen_width * screen_height);
    HDC hDC = CreateCompatibleDC(hScreen);
    point middle_screen(screen_width / 2, screen_height / 2);

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = w;
    bmi.biHeight = -h;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;

    while (run_threads) {
        Sleep(6);
        HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
        BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, middle_screen.x - (w / 2), middle_screen.y - (h / 2), SRCCOPY);
        SelectObject(hDC, old_obj);
        GetDIBits(hDC, hBitmap, 0, h, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
        bool stop_loop = false;
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w * 4; i += 4) {
                    #define red screenData[i + (j*w*4) + 2]
                    #define green screenData[i + (j*w*4) + 1]
                    #define blue screenData[i + (j*w*4) + 0]

                if (is_colorY(red, green, blue)) {
                    aim_x = (i / 4) - (w / 2);
                    //original aim_y = j - (h / 2) + 3;
                    aim_y = j - (h / 2) + snapValue;
                    stop_loop = true;
                    break;
                }
            }
            if (stop_loop) {
                break;
            }
        }
        if (!stop_loop) {
            aim_x = 0;
            aim_y = 0;
        }
    }
}

int main(void) {
    ShowCursor(false);

    //for the menu
    bool colorOptions = false;
    bool changeConfig = false;
    bool snappingArea = false;
    bool commit = false;

    //for toggle keys
    bool toggleKey = false;
    bool toggleActive = true;
    bool aim = false;
    bool changeKey = false;
    bool lClick = false;
    bool mb4 = false;
    bool mb5 = false;
    bool hold = false;

    string color;

    double sensitivity = 0.52;
    double smoothing = 0.5;
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    auto w_f = freopen("CON", "w", stdout);
    auto r_f = freopen("CON", "r", stdin);
    //start
    cout << "[+] COLOR SOFT AIM [+]" << endl;
    cout << "[-] ENTER YOUR CONFIG [-]" << endl << endl;
    cout << "[-] SENSITIVITY: ";
    cin >> sensitivity;
    cout << "[-] SMOOTHING: ";
    cin >> smoothing;
    int mode = 0;
    cout << "[-] MODE: ";
    cin >> mode;

    clear();
    cout << "CONFIGURATION SUCCESSFULLY LOADED. LOADING CHEAT OPTIONS.";
    Sleep(2000);

    Menu menu = Menu("[~] COLOR AIM MENU [~]", "[!] TO FINISH COMMIT YOUR CHANGES [!]");

    menu.AddOption("[!!] NOTHING IS DEFAULT SET EVERY SETTING HERE [!!]");
    menu.AddOption("[TAB] SET AIM COLOR");
    menu.AddOption("[F1] CHANGE SNAPPING AREA");
    menu.AddOption("[F2] CHANGE TOGGLE KEY");
    menu.AddOption("[ALT] CHANGE CONFIGURATION");
    menu.AddOption("[ESCAPE] COMMIT CHANGES");
    menu.AddOption(0, 99, false);
    menu.Print();
    while (true) {
        if (GetAsyncKeyState(VK_TAB)) {
            colorOptions = !colorOptions;

            menu.UpdateOption(1, 1);
            Sleep(1000);
            clear();
            cin.clear();
            fflush(stdin);

            cout << "[-] ENTER COLOR (CASE SENSITIVE - RED, YELLOW, PURPLE) ! RED NOT FUNCTIONAL ! : ";
            cin >> color;
            if (color == "RED") {
                cout << "[!] RED ISN'T FUNCTIONAL, GO BACK AND CHANGE YOUR CHOICE [!]" << endl;

                Sleep(1000);

                menu.UpdateOption(1, 13);
                menu.Print();
            }
            else if (color == "YELLOW") {
                cout << "[+] COLOR IS SET TO YELLOW [+]" << endl;

                Sleep(1000);

                menu.UpdateOption(1, 4);
                menu.Print();
            }
            else if (color == "PURPLE") {
                cout << "[+] COLOR IS SET TO PURPLE [+]" << endl;

                Sleep(1000);

                menu.UpdateOption(1, 5);
                menu.Print();
            }
            else {
                cout << "[!] INVALID COLOR OPTION [!]";

                menu.UpdateOption(1, 13);
                Sleep(1000);

                menu.Print();
            }
        }

        else if (GetAsyncKeyState(VK_F1)) {

            snappingArea = !snappingArea;

            menu.UpdateOption(2, 1);
            Sleep(1000);
            clear();
            cin.clear();
            fflush(stdin);

            string area;

            cout << "[-] ENTER AIMING AREA (CASE SENSITIVE - HEAD, NECK, CHEST): ";
            cin >> area;

            if (area == "HEAD") {
                snapValue = 3;
                cout << "[+] SNAPPING SET TO HEAD [+]";
                Sleep(2000);

                clear();

                menu.UpdateOption(2, 7);
                menu.Print();
            }
            else if (area == "NECK") {
                snapValue = 4;
                cout << "[+] SNAPPING SET TO NECK [+]";
                Sleep(2000);

                clear();

                menu.UpdateOption(2, 8);
                menu.Print();
            }
            else if (area == "CHEST") {
                snapValue = 10;
                cout << "[+] SNAPPING SET TO CHEST [+]";
                Sleep(2000);

                clear();

                menu.UpdateOption(2, 9);
                menu.Print();
            }
            else {
                cout << "[!] INVALID CHOICE [!]";
                menu.UpdateOption(2, 13);
                Sleep(2000);

                clear();

                menu.Print();
            }
        }

        else if (GetAsyncKeyState(VK_F2)) {
        changeKey = !changeKey;

        int choice;

        menu.UpdateOption(3, 1);
        Sleep(1000);
        clear();
        cin.clear();
        fflush(stdin);

        cout << "[1] LEFT CLICK" << endl;
        cout << "[2] MB4" << endl;
        cout << "[3] MB5" << endl;

        cout << endl << "[-] ENTER YOUR CHOICE: ";
        cin >> choice;

        if (choice == 1) {
            lClick = true;

            clear();
            cout << "[+] AIM KEY SET TO LEFT CLICK";

            cin.clear();
            fflush(stdin);

            clear();

            int changeMode;

            cout << "[1] HOLD" << endl;
            cout << "[2] TOGGLE" << endl;

            cout << "[-] ENTER YOUR CHOICE: ";
            cin >> changeMode;
            if (changeMode == 1) {
                hold = true;
                clear();
                cout << "[+] AIM KEY SET TO HOLD [+]";
                Sleep(1000);
                }
            else if (changeMode == 2) {
                clear();
                cout << "[+] AIM KEY SET TO TOGGLE [+]";
                Sleep(1000);
            }


            clear();
            Sleep(500);
            menu.UpdateOption(3, 10);
            menu.Print();
        }

        else if (choice == 2) {
            mb4 = true;

            clear();
            cout << "[+] AIM KEY SET TO MB4";

            cin.clear();
            fflush(stdin);

            clear();

            int changeMode;

            cout << "[1] HOLD" << endl;
            cout << "[2] TOGGLE" << endl;

            cout << "[-] ENTER YOUR CHOICE: ";
            cin >> changeMode;
            if (changeMode == 1) {
                hold = true;
                clear();
                cout << "[+] AIM KEY SET TO HOLD";
            }
            else if (changeMode == 2) {
                clear();
                cout << "[+] AIM KEY SET TO TOGGLE [+]";
            }


            clear();
            Sleep(500);

            menu.UpdateOption(3, 11);
            clear();

            menu.Print();
        }

        else if (choice == 3) {
            mb5 = true;

            clear();
            cout << "[+] AIM KEY SET TO MB5";

            cin.clear();
            fflush(stdin);

            clear();

            int changeMode;

            cout << "[1] HOLD" << endl;
            cout << "[2] TOGGLE" << endl;

            cout << "[-] ENTER YOUR CHOICE: ";
            cin >> changeMode;
            if (changeMode == 1) {
                hold = true;
                clear();
                cout << "[+] AIM KEY SET TO HOLD";
            }
            else if (changeMode == 2) {
                clear();
                cout << "[+] AIM KEY SET TO TOGGLE [+]";
            }


            clear();
            Sleep(500);

            menu.UpdateOption(3, 12);
            clear();

            menu.Print();
        }

        else {
            cout << "[!] INVALID CHOICE [!]";
            menu.UpdateOption(3, 13);

            clear();
            menu.Print();
        }
        }

        else if (GetAsyncKeyState(VK_MENU)) {
            changeConfig = !changeConfig;

            menu.UpdateOption(4, 1);
            Sleep(1000);
            clear();

            cout << "[-] SENSITIVITY: ";
            cin >> sensitivity;
            cout << "[-] SMOOTHING: ";
            cin >> smoothing;
            cout << "[-] MODE: ";
            cin >> mode;
            Sleep(1000);
            clear();

            cout << "[+] CONFIGURATION SAVED [+]";
            Sleep(1000);
            cin.clear();
            fflush(stdin);
            menu.UpdateOption(4, 6);
            menu.Print();
        }

        else if (GetAsyncKeyState(VK_ESCAPE)) {
                commit = !commit;
                menu.UpdateOption(1);
                if (commit) {
                    menu.UpdateProgressBar(0, 0);
                    //the loading bar to indicate that everything worked and the program didn't stall
                    for (int i = 0; i < 99; i+=6) {
                        menu.UpdateProgressBar(0, (float)i);
                        Sleep(20);
                    }
                    menu.UpdateProgressBar(0, -1);
                    menu.UpdateOption(3 ,6);

                    clear();
                    cout << endl << endl << endl;
                    cout << "[$] SUCCESS - LAUNCH YOUR GAME [$]" << endl;
                    cout << "[!] THIS PROMPT WILL CLOSE IN 5 SECONDS... [!]";
                    Sleep(5000);
                    fclose(w_f);
                    fclose(r_f);
                    FreeConsole(); // had to free console here because running the aim (below) would stall the program

                    //end

                    if (color == "PURPLE") {
                        //aim start
                        thread(bot).detach();
                    }

                    else if (color == "RED") {
                        //aim start
                        thread(botR).detach();
                    }

                    else if (color == "YELLOW") {
                        //aim start
                        thread(botY).detach();
                    }

                    auto t_start = std::chrono::high_resolution_clock::now();
                    auto t_end = std::chrono::high_resolution_clock::now();
                    auto left_start = std::chrono::high_resolution_clock::now();
                    auto left_end = std::chrono::high_resolution_clock::now();
                    double sensitivity_x = 1.0 / sensitivity / (screen_width / 1920.0) * 1.08;
                    double sensitivity_y = 1.0 / sensitivity / (screen_height / 1080.0) * 1.08;
                    bool left_down = false;

                    context = interception_create_context();
                    interception_set_filter(context, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_ALL);

                    while (interception_receive(context, device = interception_wait(context), &stroke, 1) > 0) {
                        InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&stroke;
                        t_end = std::chrono::high_resolution_clock::now();
                        double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

                        if (mstroke.state & INTERCEPTION_MOUSE_LEFT_BUTTON_UP) {
                            left_down = false;
                        }

                        if (toggleActive == true) {

                            if (hold == true) {
                                if (lClick == true) {
                                    if (mstroke.state & INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN) {
                                        aim = !aim;
                                    }
                                    if (mstroke.state & INTERCEPTION_MOUSE_LEFT_BUTTON_UP) {
                                        aim = !aim;
                                    }
                                }

                                if (mb4 == true) {
                                    if (mstroke.state & INTERCEPTION_MOUSE_BUTTON_4_DOWN) {
                                        aim = !aim;
                                    }
                                    if (mstroke.state & INTERCEPTION_MOUSE_BUTTON_4_UP) {
                                        aim = !aim;
                                    }
                                }

                                if (mb5 == true) {
                                    if (mstroke.state & INTERCEPTION_MOUSE_BUTTON_5_DOWN) {
                                        aim = !aim;
                                    }
                                    if (mstroke.state & INTERCEPTION_MOUSE_BUTTON_5_UP) {
                                        aim = !aim;
                                    }
                                }
                            }

                            if (hold == false) {
                                if (lClick == true) {
                                    if (mstroke.state & INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN) {
                                        aim = !aim;
                                    }
                                }

                                if (mb4 == true) {
                                    if (mstroke.state & INTERCEPTION_MOUSE_BUTTON_4_DOWN) {
                                        aim = !aim;
                                    }
                                }

                                if (mb5 == true) {
                                    if (mstroke.state & INTERCEPTION_MOUSE_BUTTON_5_DOWN) {
                                        aim = !aim;
                                    }
                                }
                            }


                            if (aim) {
                                CURSORINFO cursorInfo = { 0 };
                                cursorInfo.cbSize = sizeof(cursorInfo);
                                GetCursorInfo(&cursorInfo);
                                if (cursorInfo.flags != 1) {
                                    if (((mode & 1) > 0) && (mstroke.state & INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN)) {
                                        left_down = true;
                                        if (elapsed_time_ms > 7) {
                                            t_start = std::chrono::high_resolution_clock::now();
                                            left_start = std::chrono::high_resolution_clock::now();
                                            if (aim_x != 0 || aim_y != 0) {
                                                mstroke.x += double(aim_x) * sensitivity_x;
                                                mstroke.y += double(aim_y) * sensitivity_y;
                                            }
                                        }
                                    }
                                    else if (((mode & 2) > 0) && (mstroke.flags == 0)) {
                                        if (elapsed_time_ms > 7) {
                                            t_start = std::chrono::high_resolution_clock::now();
                                            if (aim_x != 0 || aim_y != 0) {
                                                left_end = std::chrono::high_resolution_clock::now();
                                                double recoil_ms = std::chrono::duration<double, std::milli>(left_end - left_start).count();
                                                double extra = 38.0 * (screen_height / 1080.0) * (recoil_ms / 1000.0);
                                                if (!left_down) {
                                                    extra = 0;
                                                }
                                                else if (extra > 38.0) {
                                                    extra = 38.0;
                                                }
                                                double v_x = double(aim_x) * sensitivity_x * smoothing;
                                                double v_y = double(aim_y + extra) * sensitivity_y * smoothing;
                                                if (fabs(v_x) < 1.0) {
                                                    v_x = v_x > 0 ? 1.05 : -1.05;
                                                }
                                                if (fabs(v_y) < 1.0) {
                                                    v_y = v_y > 0 ? 1.05 : -1.05;
                                                }
                                                mstroke.x += v_x;
                                                mstroke.y += v_y;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        interception_send(context, device, &stroke, 1);
                        //end
                        
                    }

                }
        }
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            interception_destroy_context(context);
            if (screenData) {
                free(screenData);
            }
            break;
    }

    return TRUE;
}