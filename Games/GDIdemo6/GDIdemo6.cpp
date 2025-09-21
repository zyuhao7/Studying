
//-----------------------------------【程序说明】----------------------------------------------
//  程序名称:：GDIdemo6
//	 2025年 9 月 Learning 沫羽皓
//  描述：游戏动画技巧之 定时器动画显示 示例程序
//------------------------------------------------------------------------------------------------

#include "framework.h"
#include "GDIdemo6.h"
#include <mmsystem.h>
#include <windows.h>
#include <tchar.h>//使用swprintf_s函数所需的头文件

#define MAX_LOADSTRING 100
#define WINDOW_WIDTH	800							//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define WINDOW_HEIGHT	600							//为窗口高度定义的宏，以方便在此处修改窗口高度
#define WINDOW_TITLE		L"【致我们永不熄灭的游戏开发梦想】游戏动画技巧之 定时器动画显示 示例程序"	//为窗口标题定义的宏

#pragma comment(lib,"winmm.lib")  //调用PlaySound函数所需库文件
#pragma  comment(lib,"Msimg32.lib")  //添加使用TransparentBlt函数所需的库文件

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HDC				g_hdc = NULL, g_mdc = NULL;       //全局设备环境句柄与全局内存DC句柄
HBITMAP		g_hSprite[12];     //声明位图数组用来储存各张人物位图
int					g_iNum = 0;         //"g_iNum"变量用来记录目前显示的图号

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL						Game_Init(HWND hwnd);			//在此函数中进行资源的初始化
VOID							Game_Paint(HWND hwnd);		//在此函数中进行绘图代码的书写
BOOL						Game_CleanUp(HWND hwnd);	//在此函数中进行资源的清理

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nShowCmd)
{
	//【1】窗口创建四步曲之一：开始设计一个完整的窗口类
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;							//窗口的附加内存，依然取0就行了
	wndClass.hInstance = hInstance;						//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //为hbrBackground成员指定一个白色画刷句柄	
	wndClass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = L"ForTheDreamOfGameDevelop";		//用一个以空终止的字符串，指定窗口类的名字。

	//【2】窗口创建四步曲之二：注册窗口类
	if (!RegisterClassEx(&wndClass))				//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;

	//【3】窗口创建四步曲之三：正式创建窗口
	HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOW_TITLE,				//喜闻乐见的创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//【4】窗口创建四步曲之四：窗口的移动、显示与更新
	MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true);		//调整窗口显示时的位置，使窗口左上角位于（250,80）处
	ShowWindow(hwnd, nShowCmd);    //调用ShowWindow函数来显示窗口
	UpdateWindow(hwnd);						//对窗口进行更新，就像我们买了新房子要装修一样

	//游戏资源的初始化，若初始化失败，弹出一个消息框，并返回FALSE
	if (!Game_Init(hwnd))
	{
		MessageBox(hwnd, L"资源初始化失败", L"消息窗口", 0); //使用MessageBox函数，创建一个消息窗口
		return FALSE;
	}
	PlaySound(L"鸟之诗.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //循环播放背景音乐 

	//【5】消息循环过程
	MSG msg = { 0 };				//定义并初始化msg
	while (msg.message != WM_QUIT)		//使用while循环，如果消息不是WM_QUIT消息，就继续循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);			//分发一个消息给窗口程序。
		}
	}

	//【6】窗口类的注销
	UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);  //程序准备结束，注销窗口类
	return 0;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDIDEMO6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GDIDEMO6);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    switch (message)
    {
    case WM_TIMER:
        Game_Paint(hWnd);
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hWnd);
        break;


    case WM_DESTROY:
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


BOOL Game_Init(HWND hwnd)
{
    g_hdc = GetDC(hwnd);

    wchar_t filename[20];
    for (int i = 0; i < 12; ++i)
    {
        memset(filename, 0, sizeof(filename));
        swprintf_s(filename, L"%d.bmp", i);
        g_hSprite[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT, LR_LOADFROMFILE);
       
    }

	g_mdc = CreateCompatibleDC(g_hdc);

	g_iNum = 0;
	SetTimer(hwnd, 1, 90, NULL);

	Game_Paint(hwnd);
	return TRUE;

}
VOID Game_Paint(HWND hwnd)
{
    if (g_iNum == 11) g_iNum = 0;
    SelectObject(g_mdc, g_hSprite[g_iNum]);
    BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_mdc, 0, 0, SRCCOPY);

    g_iNum++;
}
BOOL Game_CleanUp(HWND hwnd)
{
    KillTimer(hwnd, 1);
    for (int i = 0; i < 12; ++i)
    {
        DeleteObject(g_hSprite[i]);
    }
    DeleteDC(g_mdc);
    ReleaseDC(hwnd,g_mdc);
    return TRUE;
}