// GDIdemoCore.cpp : 定义应用程序的入口点。
// 
//---------------------------【程序说明】----------------------------------- 
 // 程序名称:：GDIdemoCore 
 // 2025 年 9 月 learning 沫羽皓 
 // 描述：实现 GDI 游戏开发所需的核心程序  HFont
 //------------------------------------------------------------------------

#include "framework.h"
#include "GDIdemoCore2.h"
#include <windows.h>   // 提供 MessageBox
#include <mmsystem.h>  // 提供 PlaySound
#include <time.h>
#pragma  comment(lib, "winmm.lib")

#define MAX_LOADSTRING 100
#define WINDOW_WIDTH 800 //为窗口宽度定义的宏，以方便在此处修改窗口宽度 
#define WINDOW_HEIGHT 600 //为窗口高度定义的宏，以方便在此处修改窗口高度 
#define WINDOW_TITLE L"【致我们永不熄灭的游戏开发梦想】GDI 程序核心框架" //为窗口标题定义的宏

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HDC g_hdc = NULL; //全局设备环境句柄
HPEN g_hPen[7] = { 0 }; //定义画笔句柄的数组 
HBRUSH g_hBrush[7] = { 0 }; //定义画刷句柄的数组 
int g_iPenStyle[7] = { PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,PS_NULL,PS_INSIDEFRAME }; //定义画笔样式数组并初始化 
int g_iBrushStyle[6] = { HS_VERTICAL,HS_HORIZONTAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_BDIAGONAL }; //定义画刷样式数组并初始化 

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL Game_Init(HWND hwnd); //在此函数中进行资源的初始化 
VOID Game_Paint(HWND hwnd); //在此函数中进行绘图代码的书写 
BOOL Game_CleanUp(HWND hwnd); //在此函数中进行资源的清理


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nShowCmd)
{
    //【1】窗口创建四步曲之一：开始设计一个完整的窗口类 
    WNDCLASSEX wndClass = { 0 };
    wndClass.cbSize = sizeof(wndClass); // 设置结构体的字节数大小
    wndClass.style = CS_HREDRAW | CS_VREDRAW; //设置窗口的样式 
    wndClass.lpfnWndProc = WndProc; //设置指向窗口过程函数的指针 
    wndClass.cbClsExtra = 0; //窗口类的附加内存，取 0 就可以了 
    wndClass.cbWndExtra = 0; //窗口的附加内存，依然取 0 就行了 
    wndClass.hInstance = hInstance; //指定包含窗口过程的程序的实例句柄。
    wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); // //本地加载自定义 icon 图标 
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //指定窗口类的光标句柄。
    wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); //为hbrBackground 成员指定一个灰色画刷句柄
    wndClass.lpszMenuName = NULL; //用一个以空终止的字符串，指定菜单资源的名字。
    wndClass.lpszClassName = L"ForTheDreamOfGameDevelop"; //用一个以空终止的字符串，指定窗口类的名字。

    //【2】窗口创建四步曲之二：注册窗口类 
    if (!RegisterClassEx(&wndClass)) //设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
    {
        return -1;
    }

    // 【3】窗口创建四步曲之三：正式创建窗口 
    HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOW_TITLE, //喜闻	乐见的创建窗口函数 CreateWindow
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
        WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

    //【4】窗口创建四步曲之四：窗口的移动、显示与更新 
    MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true); //调整窗口显示时的位置，使窗口左上角位于（250, 80）处
    ShowWindow(hwnd, nShowCmd); //调用 ShowWindow 函数来显示窗口 
    UpdateWindow(hwnd); //对窗口进行更新，就像我们买了新房子要装修一样 

    //游戏资源的初始化，若初始化失败，弹出一个消息框，并返回 FALSE 
    if (!Game_Init(hwnd))
    {
        MessageBox(hwnd, L"资源初始化失败", L"消息窗口", 0); //使用 MessageBox 函数，创建一个消息窗口
        return FALSE;
    }

    PlaySound(L"AIR - 夏影.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //【5】消息循环过程 
    MSG msg = { 0 }; // 定义并初始化 msg
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    //【6】窗口类的注销 
    UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance); //程序准备结束，注销窗口类
    return 0;
}


BOOL Game_Init(HWND hwnd)
{
    g_hdc = GetDC(hwnd);
    srand((unsigned)time(NULL)); // 初始化时间种子

    // 随机初始化画笔和画刷的颜色值
    for (int i = 0; i <= 6; ++i)
    {
        g_hPen[i] = CreatePen(g_iPenStyle[i], i, RGB(rand() % 256, rand() % 256, rand() % 256));
        if (i == 6)
            g_hBrush[i] = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        else
            g_hBrush[i] = CreateHatchBrush(g_iBrushStyle[i], RGB(rand() % 256, rand() % 256, rand() % 256));
    }

    Game_Paint(hwnd);
    ReleaseDC(hwnd, g_hdc);
    return TRUE;
}

VOID Game_Paint(HWND hwnd)
{
    HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑"); 
    SelectObject(g_hdc, hFont);
    SetBkMode(g_hdc, TRANSPARENT); //设置输出文字背景为透明
    
    // 定义三段文字
    wchar_t text1[] = L"我们所有的梦想都可以实现, 只要我们有勇气去追求他们.";
	wchar_t text2[] = L"All our dreams can come true, if we have the courage to pursue them. ";
	wchar_t text3[] = L"-------------------沃尔特 迪斯尼";

    // 设置文字颜色并输出第一段文字
    SetTextColor(g_hdc, RGB(50, 255, 50));
    TextOut(g_hdc, 30, 150, text1, wcslen(text1));

	// 设置文字颜色并输出第二段文字
	SetTextColor(g_hdc, RGB(50, 50, 255));
	TextOut(g_hdc, 30, 200, text2, wcslen(text2));

	// 设置文字颜色并输出第三段文字
	SetTextColor(g_hdc, RGB(255, 150, 50));
	TextOut(g_hdc, 500, 250, text3, wcslen(text3));

    DeleteObject(hFont); 
}
BOOL Game_CleanUp(HWND hwnd)
{

    for (int i = 0; i <= 6; ++i)
    {
        DeleteObject(g_hPen[i]);
        DeleteObject(g_hBrush[i]);
    }

    return TRUE;
}


//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDIDEMOCORE2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GDIDEMOCORE2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT paintStruct;

    switch (message)
    {
    case WM_KEYDOWN: // 若是键盘按下消息
        if (wParam == VK_ESCAPE) // 若被按下的是 ESC
            DestroyWindow(hWnd); // 销毁窗口, 并发送一条 WM_DESTROY 的消息
        break;

    case WM_PAINT:// 如何去重绘消息
        g_hdc = BeginPaint(hWnd, &paintStruct); // 指定窗口进行绘图工作的准备, 并和绘图有关的信息填充到 paintStrcut结构体中
        Game_Paint(hWnd);
        EndPaint(hWnd, &paintStruct); // EndPaint 函数标记指定函数的绘画过程结束
        ValidateRect(hWnd, NULL); // 更新客户区的显示
        break;

    case WM_DESTROY: // 若是窗口销毁消息
        Game_CleanUp(hWnd);

        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


/*
*

  创建画笔
    HPEN CreatePen(
        __in int fnPenStyle, //画笔样式
        __in int nWidth, //线条宽度
        __in COLORREF crColor //线条颜色
        );

    COLORREF RGB(
         BYTE byRed, //颜色的红色分量值，在 0~255 之间取值
         BYTE byGreen, //颜色的绿色分量值，在 0~255 之间取值
         BYTE byBlue //颜色的蓝色分量值，在 0~255 之间取值
    );

      创建画刷
    HBRUSH CreateSolidBrush(
        __in COLORREF crColor
    );

      阴影画刷
    HBRUSH CreateHatchBrush(
         __in int fnStyle, //阴影样式
         __in COLORREF clr_ref //前景色颜色值
    );

      绘制线条
    BOOL LineTo(
         __in HDC hdc, //设备环境句柄
         __in int nXEnd, //线条终点 x 坐标值
         __in int nYEnd //线条终点 y 坐标值
    );

      文字输出
     BOOL TextOut(
     HDC hdc, //需要进行文本输出的 DC 的句柄
     int nXStart, // 开始书写的位置的 X 坐标
     int nYStart, //开始书写的位置的 Y 坐标
     LPCTSTR lpString, // 指向字符串的指针
     int cbString // 字符串的字符数
    );

      进阶文字输出函数
     int DrawText(
     HDC hDC, // 需要进行文本输出的 DC 设备环境句柄
     LPCTSTR lpString, // 指向需要写入的字符串的指针
     int nCount, // 需要写入的字符串的长度
     LPRECT lpRect, // 指向包含了绘制区域的矩形结构体的指针
     UINT uFormat // 书写模式的标识，有多种定制标识可以选择
    );

      设置文字颜色
     COLORREF SetTextColor(
     HDC hdc, // 设备环境句柄
     COLORREF crColor // 需要设置的文本颜色
    );

      设置文字背景透明
     int SetBkMode(
     HDC hdc, //设备环境的句柄
     int iBkMode // mode 是要设置的模式，我们常设为 TRANSPARENT。
    );

      加载位图
	 HANDLE LoadImage(
      HINSTANCE hinst, //来源实例句柄
      LPCTSTR lpszName, //名称
      UINT uType, //加载的类型
      int cxDesired, //指定存储的宽度
      int cyDesired, //指定存储的高度
      UINT fuLoad //加载的方式，
     );
*/
