#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <commctrl.h>

#define MYERRORTEXT TEXT("Error:Program initialisation process.")
HINSTANCE hInstGlob;
int MyCmdShow ;
char szClassName[] = "WindowsApp";
HWND Form1; //Windows handler
FILE *file1; //for file operations
POINT MousePos; //for mouser cursor coordinates
LRESULT CALLBACK WndProc0(HWND, UINT, WPARAM, LPARAM);

//popup message boxes
void ShowMessage(LPCTSTR mymessage, LPCTSTR mycaption, HWND sender);
int QuestionBox(LPCTSTR mymessage, LPCTSTR mycaption, HWND sender);

HWND VScrollBar1;
#define OBJ_ID100 100

//*********************************
//The program's entry point
//*********************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("StdWinClassName");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass0;
    MyCmdShow  = iCmdShow;
    hInstGlob = hInstance;
    LoadLibrary(L"COMCTL32.DLL");

    //*********************************
    //Preparing the windows object
    //*********************************
    wndclass0.style = CS_HREDRAW | CS_VREDRAW;
    wndclass0.lpfnWndProc = WndProc0;
    wndclass0.cbClsExtra = 0;
    wndclass0.cbWndExtra = 0;
    wndclass0.hInstance = hInstance;
    wndclass0.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass0.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass0.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//LTGRAY_BRUSH
    wndclass0.lpszMenuName = NULL;
    wndclass0.lpszClassName = TEXT("WIN0");

    //*********************************
    //Registering the window data
    //*********************************
    if (!RegisterClass(&wndclass0))
    {
        MessageBox(NULL, MYERRORTEXT, TEXT("Program Start"), MB_ICONERROR); return 0;
    }

    //*********************************
    //Creating the window
    //*********************************
    Form1 = CreateWindow(TEXT("WIN0"),
        TEXT("WIN32 API"),
        (WS_OVERLAPPED | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX),
        50,
        50,
        400,
        300,
        NULL,
        NULL,
        hInstance,
        NULL);

    //*********************************
    //Showing the window
    //*********************************
    ShowWindow(Form1, MyCmdShow );
    UpdateWindow(Form1);

    //*********************************
    //Managing message handling
    //*********************************
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

//*********************************
//The window’s callback function (windows procedure)
//*********************************
LRESULT CALLBACK WndProc0(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (message)
    {
        //*********************************
        //Creating the window
        //*********************************
    case WM_CREATE:
        /*Init*/;
        VScrollBar1 = CreateWindow(TEXT("scrollbar"), (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | SBS_VERT, 10, 10, 30, 150
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        SendMessage(VScrollBar1, SBM_SETRANGE, 10, 100);
        SendMessage(VScrollBar1, SBM_SETPOS, 20, TRUE);
        return 0;
        //*********************************
        //Handle scrolling
        //*********************************
    case WM_HSCROLL:
        switch (LOWORD(wParam))
        {
            ;
        }
        return 0;
    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_LINEDOWN:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
            case OBJ_ID100:
                MessageBoxA(NULL, "Clicking down", "User interaction", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;
        case SB_LINEUP:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
            case OBJ_ID100:
                MessageBoxA(NULL, "Clicking up", "User interaction", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;

        case SB_PAGEDOWN:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
            case OBJ_ID100:
                int s1;
                char mymessage[256], ertek[256];

                strcpy_s(mymessage, "Paging down, new position: ");
                s1 = SendMessage(VScrollBar1, SBM_GETPOS, 0, 0);
                _itoa_s(s1 + 10, ertek, 10);
                strcat_s(mymessage, ertek);
                SendMessage(VScrollBar1, SBM_SETPOS, s1 + 10, TRUE);
                MessageBoxA(NULL, mymessage, "User interaction", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;
        case SB_PAGEUP:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
            case OBJ_ID100:
                int s1;
                char mymessage[256], ertek[256];

                strcpy_s(mymessage, "Paging up, new position: ");
                s1 = SendMessage(VScrollBar1, SBM_GETPOS, 0, 0);
                _itoa_s(s1 - 10, ertek, 10);
                strcat_s(mymessage, ertek);
                SendMessage(VScrollBar1, SBM_SETPOS, s1 - 10, TRUE);
                MessageBoxA(NULL, mymessage, "User interaction", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;
        case SB_THUMBPOSITION:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
                ;
            case OBJ_ID100:
                MessageBoxA(NULL, "Moving the slider", "User interaction", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;
        case SB_THUMBTRACK:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
                ;
            case OBJ_ID100:
                MessageBoxA(NULL, "Slider moved", "User interaction", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;

        }
        return 0;
        //*********************************
        //special message
        //*********************************
    case WM_NOTIFY: {
        return 0; }
                  //*********************************
                  //left mouse button released
                  //*********************************
    case WM_LBUTTONUP:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //middle mouse button
        //*********************************
    case WM_MBUTTONUP:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //right mouse button released
        //*********************************
    case WM_RBUTTONUP:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //messages for Windows controls
        //*********************************
    case WM_COMMAND:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //Resizing the window
        //*********************************
    case WM_SIZE:
        return 0;

        //*********************************
        //Redrawing the client area
        //*********************************
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
        //*********************************
        //Closing the window
        //*********************************
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
        //*********************************
        //Destroying the window
        //*********************************
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//*********************************
//Dialog box with an OK button
//*********************************
void ShowMessage(LPCTSTR mymessage, LPCTSTR mycaption, HWND sender)
{
    MessageBox(sender, mymessage, mycaption, MB_OK);
}

//*********************************
//Dialog box with YES-NO buttons
//*********************************
int QuestionBox(LPCTSTR mymessage, LPCTSTR mycaption, HWND sender)
{
    return MessageBox(sender, mymessage, mycaption, MB_YESNO);
}
