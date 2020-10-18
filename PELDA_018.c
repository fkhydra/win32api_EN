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

HWND ListView1;
#define OBJ_ID100 100

void AddLVColumn(HWND LVObject, int colnum, int colwidth, wchar_t *coltitle);
void AddLVItem(HWND LVObject, int mainitem, TCHAR* coltitle);
void AddLVSubItem(HWND LVObject, int mainitem, int subitem, TCHAR* coltitle);

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
        ListView1 = CreateWindowEx(0, WC_LISTVIEW, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS, 10, 10, 500, 400
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        SendMessage(ListView1, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
        
        AddLVColumn(ListView1, 0, 80,(wchar_t *)L"Header 1");
        AddLVColumn(ListView1, 1, 80, (wchar_t*)L"Header 2");
        AddLVColumn(ListView1, 2, 80, (wchar_t*)L"Header 3");

        AddLVItem(ListView1,0, (wchar_t*)L"Item1");
        AddLVItem(ListView1, 1, (wchar_t*)L"Item2");

        AddLVSubItem(ListView1, 0, 2, (wchar_t*)L"Item3");
        AddLVSubItem(ListView1, 1, 1, (wchar_t*)L"Item4");
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
        switch (LOWORD(wParam))
        {
            case OBJ_ID100:
            {
                if (((LPNMHDR)lParam)->code == NM_CLICK)
                {
                    TCHAR myText[255];
                    int iSlected = 0;
                    LV_ITEM LvItem;
                    iSlected = SendMessage(ListView1, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                    if (iSlected != -1)
                    {
                        memset(&LvItem, 0, sizeof(LvItem));
                        LvItem.mask = LVIF_TEXT;
                        LvItem.iSubItem = 0;
                        LvItem.pszText = myText;
                        LvItem.cchTextMax = 256;
                        LvItem.iItem = iSlected;
                        SendMessage(ListView1, LVM_GETITEMTEXT, iSlected, (LPARAM)&LvItem);
                        wcscpy_s(myText, 255, LvItem.pszText);
                        MessageBox(NULL, myText, L"User interaction", MB_OK | MB_ICONINFORMATION);
                        break;
                    }
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

void AddLVColumn(HWND LVObject, int colnum, int colwidth, wchar_t *coltitle)
{
    TCHAR myText[256];
    LV_COLUMN mycolumn;
    memset(&mycolumn, 0, sizeof(mycolumn));
    wcscpy_s(myText, coltitle);
    mycolumn.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
    mycolumn.cx = colwidth;
    mycolumn.pszText = myText;
    mycolumn.cchTextMax = sizeof(myText);
    SendMessage(LVObject, LVM_INSERTCOLUMN, colnum, (LPARAM)&mycolumn);
}

void AddLVItem(HWND LVObject, int mainitem, TCHAR* coltitle)
{
    TCHAR myText[256];
    LV_ITEM myItem;
    memset(&myItem, 0, sizeof(myItem));
    wcscpy_s(myText, coltitle);
    myItem.mask = LVIF_TEXT;
    myItem.iItem = mainitem;
    myItem.iSubItem = 0;
    myItem.pszText = coltitle;
    myItem.cchTextMax = sizeof(coltitle);
    SendMessage(LVObject, LVM_INSERTITEM, 0, (LPARAM)&myItem);
}

void AddLVSubItem(HWND LVObject, int mainitem, int subitem, TCHAR* coltitle)
{
    LV_ITEM myItem;
    memset(&myItem, 0, sizeof(myItem));
    myItem.mask = LVIF_TEXT;
    myItem.iItem = mainitem;
    myItem.iSubItem = subitem;
    myItem.pszText = coltitle;
    myItem.cchTextMax = sizeof(coltitle);
    SendMessage(LVObject, LVM_SETITEM, 0, (LPARAM)&myItem);
}
