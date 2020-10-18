#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <commctrl.h>

#define MYERRORTEXT TEXT("Error:Program initialisation process.")
HINSTANCE hInstGlob;
int MyCmdShow ;
char szClassName[] = "WindowsApp";
HWND Form1; //Windows handler
FILE* file1; //for file operations
POINT MousePos; //for mouser cursor coordinates
LRESULT CALLBACK WndProc0(HWND, UINT, WPARAM, LPARAM);

//popup message boxes
void ShowMessage(LPCTSTR mymessage, LPCTSTR mycaption, HWND sender);
int QuestionBox(LPCTSTR mymessage, LPCTSTR mycaption, HWND sender);

HWND HTrackBar1;
HWND VTrackBar1;
#define OBJ_ID100 100
#define OBJ_ID101 101

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
        HTrackBar1 = CreateWindowEx(0, TRACKBAR_CLASS, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_AUTOTICKS, 50, 50, 170, 30
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        SendMessage(HTrackBar1, TBM_SETRANGEMIN, TRUE, 0);
        SendMessage(HTrackBar1, TBM_SETRANGEMAX, TRUE, 100);
        SendMessage(HTrackBar1, TBM_SETPAGESIZE, 0, 10);
        SendMessage(HTrackBar1, TBM_SETTICFREQ, 10, 0);
        SendMessage(HTrackBar1, TBM_SETPOS, TRUE, 50);

        VTrackBar1 = CreateWindowEx(0, TRACKBAR_CLASS, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | TBS_VERT | TBS_AUTOTICKS, 250, 50, 30, 150
            , hwnd, (HMENU)(OBJ_ID101), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        SendMessage(VTrackBar1, TBM_SETRANGEMIN, TRUE, 0);
        SendMessage(VTrackBar1, TBM_SETRANGEMAX, TRUE, 100);
        SendMessage(VTrackBar1, TBM_SETPAGESIZE, 0, 10);
        SendMessage(VTrackBar1, TBM_SETTICFREQ, 10, 0);
        SendMessage(VTrackBar1, TBM_SETPOS, TRUE, 50);
        return 0;
        //*********************************
        //Handle scrolling
        //*********************************
    case WM_HSCROLL:
        switch (LOWORD(wParam))
        {
        case TB_ENDTRACK:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
            case OBJ_ID100:
                char mymessage[256], myValue[256];
                int myPosition;

                strcpy_s(mymessage, "Current position: ");
                myPosition = SendMessageA(HTrackBar1, TBM_GETPOS, 0, 0);
                _itoa_s(myPosition, myValue, 10);
                strcat_s(mymessage, myValue);
                MessageBoxA(NULL, mymessage, "User interaction", MB_OK | MB_ICONINFORMATION);
                break;
            }
        }
        break;
        }
        return 0;
    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case TB_ENDTRACK:
        {
            int s1;
            s1 = GetWindowLong((HWND)lParam, GWL_ID);
            switch (s1)
            {
            case OBJ_ID101:
                char mymessage[256], myValue[256];
                int myPosition;

                strcpy_s(mymessage, "Current position: ");
                myPosition = SendMessageA(HTrackBar1, TBM_GETPOS, 0, 0);
                _itoa_s(myPosition, myValue, 10);
                strcat_s(mymessage, myValue);
                MessageBoxA(NULL, mymessage, "User interaction", MB_OK | MB_ICONINFORMATION);
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
