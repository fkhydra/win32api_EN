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

HWND TreeView1;
HWND Button1;
#define OBJ_ID100 100
#define OBJ_ID101 101

void AddTreeviewItem(HWND hwndTV, TCHAR lpszItem[], int nlevel);

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
        TreeView1 = CreateWindowEx(0, WC_TREEVIEW, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | TVS_DISABLEDRAGDROP | TVS_HASBUTTONS | TVS_HASLINES, 50, 50, 200, 150
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        TCHAR mylabel[256];
        wcscpy_s(mylabel,L"MainItem");
        AddTreeviewItem(TreeView1, mylabel,1);
        wcscpy_s(mylabel, L"Item 1");
        AddTreeviewItem(TreeView1, mylabel, 2);
        wcscpy_s(mylabel, L"Item 2");
        AddTreeviewItem(TreeView1, mylabel, 2);
        wcscpy_s(mylabel, L"Item 3");
        AddTreeviewItem(TreeView1, mylabel, 3);
        wcscpy_s(mylabel, L"Item 4");
        AddTreeviewItem(TreeView1, mylabel, 3);
        wcscpy_s(mylabel, L"Item 5");
        AddTreeviewItem(TreeView1, mylabel, 3);
        wcscpy_s(mylabel, L"Item 6");
        AddTreeviewItem(TreeView1, mylabel, 3);

        Button1 = CreateWindow(TEXT("button"), TEXT("MyButton")
            , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 10, 200, 150, 30
            , hwnd, (HMENU)(OBJ_ID101), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
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
        switch (((LPNMHDR)lParam)->code)
        {
            case NM_CLICK:
            {
                switch (((LPNMHDR)lParam)->idFrom)
                {
                case OBJ_ID100:
                    //A list item is selected
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
        switch (LOWORD(wParam))
        {
        case OBJ_ID101:
            WCHAR myText[256];
            WCHAR mymessage[256];
            HTREEITEM myItem;
            TV_ITEMW listitemdata;

            myItem = (HTREEITEM)SendDlgItemMessage(hwnd, OBJ_ID100, TVM_GETNEXTITEM, TVGN_CARET, (LPARAM)NULL);
            listitemdata.hItem = myItem;
            listitemdata.mask = TVIF_TEXT;
            listitemdata.pszText = myText;
            listitemdata.cchTextMax = wcslen(myText);
            SendDlgItemMessage(hwnd, OBJ_ID100, TVM_GETITEM, TVGN_CARET, (LPARAM)&listitemdata);
            
            wcscpy_s(mymessage,L"A Selected item: ");
            wcscat_s(mymessage,myText);
            MessageBox(NULL, mymessage, L"User interaction", MB_OK | MB_ICONINFORMATION);
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

void AddTreeviewItem(HWND hwndTV, TCHAR lpszItem[], int nlevel)
{
    TVITEM tvi;
    TVINSERTSTRUCT tvins;
    static HTREEITEM hprev = (HTREEITEM)TVI_FIRST;
    static HTREEITEM hprevrootitem = NULL;
    static HTREEITEM hprevlev2item = NULL;
    static HTREEITEM hprevlev3item = NULL;
    static HTREEITEM hprevlev4item = NULL;
    static HTREEITEM hprevlev5item = NULL;
    static HTREEITEM hprevlev6item = NULL;
    static HTREEITEM hprevlev7item = NULL;
    static HTREEITEM hprevlev8item = NULL;
    static HTREEITEM hprevlev9item = NULL;
    static HTREEITEM hprevlev10item = NULL;

    if (nlevel < 1 || nlevel>10) { return; }
    tvi.mask = TVIF_TEXT | TVIF_PARAM;
    tvi.pszText = lpszItem;
    tvi.cchTextMax = sizeof(tvi.pszText) / sizeof(tvi.pszText[0]);
    tvi.lParam = (LPARAM)nlevel;
    tvins.item = tvi;
    tvins.hInsertAfter = hprev;
    if (nlevel == 1) { tvins.hParent = TVI_ROOT; }
    else if (nlevel == 2) { tvins.hParent = hprevrootitem; }
    else if (nlevel == 3) { tvins.hParent = hprevlev2item; }
    else if (nlevel == 4) { tvins.hParent = hprevlev3item; }
    else if (nlevel == 5) { tvins.hParent = hprevlev4item; }
    else if (nlevel == 6) { tvins.hParent = hprevlev5item; }
    else if (nlevel == 7) { tvins.hParent = hprevlev6item; }
    else if (nlevel == 8) { tvins.hParent = hprevlev7item; }
    else if (nlevel == 9) { tvins.hParent = hprevlev8item; }
    else if (nlevel == 10) { tvins.hParent = hprevlev9item; }
    else { tvins.hParent = hprevlev9item; }
    hprev = (HTREEITEM)SendMessage(hwndTV, TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
    if (nlevel == 1) { hprevrootitem = hprev; }
    else if (nlevel == 2) { hprevlev2item = hprev; }
    else if (nlevel == 3) { hprevlev3item = hprev; }
    else if (nlevel == 4) { hprevlev4item = hprev; }
    else if (nlevel == 5) { hprevlev5item = hprev; }
    else if (nlevel == 6) { hprevlev6item = hprev; }
    else if (nlevel == 7) { hprevlev7item = hprev; }
    else if (nlevel == 8) { hprevlev8item = hprev; }
    else if (nlevel == 9) { hprevlev9item = hprev; }
    else if (nlevel == 10) { hprevlev10item = hprev; }
}
