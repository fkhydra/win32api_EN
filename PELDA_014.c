#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <commctrl.h>
#include <richedit.h>

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

HWND RichEdit1;
#define OBJ_ID100 100

BOOL REdit_loader(HWND hwndREdit, const char *pstrFileName);

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
    LoadLibrary(TEXT("RICHED32.DLL"));

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
        RichEdit1 = CreateWindow(TEXT("richedit"), TEXT("")
            , WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 50, 50, 200, 100
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        SendMessage(RichEdit1, EM_SETBKGNDCOLOR, 0, RGB(240, 240, 240));
        REdit_loader(RichEdit1, "mytext.rtf");
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

BOOL REdit_loader(HWND hwndREdit, const char *pstrFileName)
{
 BYTE swap;
 DWORD read_in_length;
 HANDLE hFile;
 int i, file_length, check_encoding;
 TCHAR* pBuffer, * pText, * pConv;

 // open file
 SetWindowText(hwndREdit, TEXT(""));
 if (INVALID_HANDLE_VALUE ==
  (hFile = CreateFileA(pstrFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)))
 {
  return FALSE;
 }

 // reading file content
 file_length = GetFileSize(hFile, NULL);
 pBuffer = (TCHAR*)malloc(file_length + 2);
 ReadFile(hFile, pBuffer, file_length, &read_in_length, NULL);
 CloseHandle(hFile);
 pBuffer[file_length] = '\0';
 pBuffer[file_length + 1] = '\0';

 //handling UNICODE content
 check_encoding = IS_TEXT_UNICODE_SIGNATURE | IS_TEXT_UNICODE_REVERSE_SIGNATURE;

 if (IsTextUnicode(pBuffer, file_length, &check_encoding))
 {
  pText = pBuffer + 2; file_length -= 2;

  if (check_encoding & IS_TEXT_UNICODE_REVERSE_SIGNATURE)
  {
   for (i = 0; i < file_length / 2; i++)
   {
    swap = ((BYTE*)pText)[2 * i];
    ((BYTE*)pText)[2 * i] = ((BYTE*)pText)[2 * i + 1];
    ((BYTE*)pText)[2 * i + 1] = swap;
   }
  }

  pConv = (TCHAR*)malloc(file_length + 2);

#ifndef UNICODE
  WideCharToMultiByte(CP_ACP, 0, (PWSTR)pText, -1, pConv, file_length + 2, NULL, NULL);
#else
  lstrcpy((PTSTR)pConv, (PTSTR)pText);
#endif
 }
 else   // non-Unicode content
 {
  pText = pBuffer;
  pConv = (TCHAR*)malloc(2 * file_length + 2);
#ifdef UNICODE
  MultiByteToWideChar(CP_ACP, 0, (LPCCH)pText, -1, (PTSTR)pConv, file_length + 1);
#else
  lstrcpy((PTSTR)pConv, (PTSTR)pText);
#endif
 }
 SetWindowText(hwndREdit, (PTSTR)pConv);
 free(pBuffer);
 free(pConv);
 return TRUE;
}
