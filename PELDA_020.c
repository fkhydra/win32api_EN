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

HWND Header2;
#define OBJ_ID100 100

void SetHeaderColText(HWND obj, int colnum, TCHAR* mymessage);
void GetHeaderColText(HWND obj, int colnum, TCHAR* mymessage);
void SetHeaderColWidth(HWND obj, int colnum, int width);
void GetHeaderColWidth(HWND obj, int colnum, int* width);

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
        Header2 = CreateWindowEx(0, WC_HEADER, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | HDS_HORZ | HDS_BUTTONS, 50, 50, 250, 40
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        {
            TCHAR myText[256];
            HD_ITEM Item;
            wcscpy_s(myText, L"Column 1");
            Item.mask = HDI_TEXT | HDI_WIDTH;
            Item.cchTextMax = 7;
            Item.fmt = HDF_LEFT;
            Item.cxy = 70;
            Item.pszText = myText;
            SendMessage(Header2, HDM_INSERTITEM, 0, (LPARAM)&Item);
            wcscpy_s(myText, L"Column 2");
            Item.mask = HDI_TEXT | HDI_WIDTH;
            Item.cchTextMax = 7;
            Item.fmt = HDF_LEFT;
            Item.cxy = 170;
            Item.pszText = myText;
            SendMessage(Header2, HDM_INSERTITEM, 1, (LPARAM)&Item);
        }

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
        switch (((LPNMHEADER)lParam)->hdr.code)
        {
            case HDN_ITEMCLICK:
            {
                switch (((LPNMHEADER)lParam)->hdr.idFrom)
                {
                case OBJ_ID100:
                    MessageBoxA(NULL, "Clicking.", "User interaction", MB_OK | MB_ICONINFORMATION);
                    break;
                }
                break;
            }
            case HDN_ENDTRACK:
            {
                switch (((LPNMHEADER)lParam)->hdr.idFrom)
                {
                case OBJ_ID100:
                    MessageBoxA(NULL, "Resizing.", "User interaction", MB_OK | MB_ICONINFORMATION);
                    break;
                }
                break;
            }
        }
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

void SetHeaderColText(HWND obj, int colnum, TCHAR* mymessage)
{
    HD_ITEM Item;
    Item.mask = HDI_TEXT;
    Item.pszText = mymessage;
    Item.cchTextMax = sizeof(mymessage);
    Item.fmt = HDF_LEFT;
    SendMessage(obj, HDM_SETITEM, colnum, (LPARAM)&Item);
}

void GetHeaderColText(HWND obj, int colnum, TCHAR* mymessage)
{
    HD_ITEM Item;
    Item.mask = HDI_TEXT;
    Item.pszText = mymessage;
    Item.cchTextMax = 256;
    SendMessage(obj, HDM_GETITEM, colnum, (LPARAM)&Item);
}

void SetHeaderColWidth(HWND obj, int colnum, int width)
{
    HD_ITEM Item;
    Item.mask = HDI_WIDTH;
    Item.cxy = width;
    SendMessage(obj, HDM_SETITEM, colnum, (LPARAM)&Item);
}

void GetHeaderColWidth(HWND obj, int colnum, int* width)
{
    HD_ITEM Item;
    Item.mask = HDI_WIDTH;
    SendMessage(obj, HDM_GETITEM, colnum, (LPARAM)&Item);
    *width = Item.cxy;
}
