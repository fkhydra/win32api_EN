#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <wchar.h>

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

HWND Button1, Button2;
HWND Edit1;
#define OBJ_ID100 100
#define OBJ_ID101 101
#define OBJ_ID102 102

HGLOBAL hMem;

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
        Button1 = CreateWindow(TEXT("button"), TEXT("Copy")
            , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 50, 150, 120, 30
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        Button2 = CreateWindow(TEXT("button"), TEXT("Paste")
            , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 200, 150, 120, 30
            , hwnd, (HMENU)(OBJ_ID101), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        Edit1 = CreateWindow(TEXT("edit"), TEXT("Enter text here")
            , WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | WS_HSCROLL | WS_VSCROLL, 50, 50, 300, 60
            , hwnd, (HMENU)(OBJ_ID102), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
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
            ;
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
        int len;
        char myText[256];

        switch (LOWORD(wParam))
        {
         case OBJ_ID100:
            GetWindowTextA(Edit1, myText, GetWindowTextLength(Edit1) + 1);
            len = strlen(myText) + 1;
            hMem = GlobalAlloc(GMEM_MOVEABLE, len);
            memcpy_s((char *)GlobalLock(hMem), len, myText, len);
            GlobalUnlock(hMem);
            OpenClipboard(hwnd);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hMem);
            CloseClipboard();
            MessageBoxA(NULL, "Text copied to ClipBoard!", "User interaction", MB_OK | MB_ICONINFORMATION);
            break;
         case OBJ_ID101:
             OpenClipboard(hwnd);
             if (hMem = GetClipboardData(CF_TEXT))
             {
                 //myText = (LPSTR)GlobalLock(hMem);
                 memcpy_s(myText, GlobalSize(hMem), (char*)GlobalLock(hMem), GlobalSize(hMem));
                 GlobalUnlock(hMem);
             }
             CloseClipboard();

             MessageBoxA(NULL, "Text inserted from ClipBoard!", "User interaction", MB_OK | MB_ICONINFORMATION);
             SetWindowTextA(Edit1,myText);
             break;
        }
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
