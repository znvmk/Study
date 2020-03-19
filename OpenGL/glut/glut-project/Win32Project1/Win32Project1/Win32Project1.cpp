// Win32Project1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Project1.h"
#include<time.h>

/*定义装载字符串的最大长度*/
#define MAX_LOADSTRING 100
#define WM_TIMER_CLOCK WM_USER+20
/*定义时钟刷新时间间隔*/
#define WM_CLOCK_INTERVAL 1000

// 全局变量: 
HINSTANCE hInst;                                // 当前实例/*定义实例句柄*/
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

/*当前时间*/
struct tm* newdate;
/*时间描述*/
time_t  long_date;
/*定时器文本*/
//TCHAR szTimerTitle[MAX_LOADSTRING];
char szTimerTitle[MAX_LOADSTRING];


// 此代码模块中包含的函数的前向声明: 
/*注册窗口类*/
ATOM                MyRegisterClass(HINSTANCE hInstance);
/*初始化实例*/
BOOL                InitInstance(HINSTANCE, int);
/*窗口处理函数*/
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
/*关于函数*/
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/*主函数*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。


    // 初始化全局字符串
	/*装载应用程序标题*/
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	/*注册应用程序类*/
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
	/*完成应用程序初始化*/
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	/*定义加速键变量*//*装载加速键*/
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	/*定义消息*/
    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		/*转换快捷键消息*/
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
			/*转换消息*/
            TranslateMessage(&msg);
			/*调度消息*/
            DispatchMessage(&msg);
        }
    }

	/*返回消息的参数*/
    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	/*定义注册窗口类的结构变量*/
    WNDCLASSEXW wcex;

	/*为结构大小成员赋值*/
    wcex.cbSize = sizeof(WNDCLASSEX);

	/*赋值窗口的样式成员*/
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	/*赋值窗口的处理函数*/
    wcex.lpfnWndProc    = WndProc;
	/*赋值窗口类的数据长度*/
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
	/*赋值窗口类的实例句柄*/
    wcex.hInstance      = hInstance;
	/*图标*/
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	/*光标*/
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	/*背景颜色*/
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	/*菜单*/
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	/*窗口类名*/
    wcex.lpszClassName  = szWindowClass;
	/*小图标*/
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	/*注册窗口类*/
    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
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

   /*创建失败，则返回*/
   if (!hWnd)
   {
      return FALSE;
   }

   /*显示窗口*/
   ShowWindow(hWnd, nCmdShow);
   /*更新窗口*/
   UpdateWindow(hWnd);

   /*创建定时器*/
   SetTimer(hWnd, WM_TIMER_CLOCK, WM_CLOCK_INTERVAL, NULL);
   /*返回*/

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*根据消息类型执行相应的操作*/
    switch (message)
    {

	/*如果是WM_COMMAND类型的*/
    case WM_COMMAND:
        {
			/*获取发送消息的命令对象ID*/
            int wmId = LOWORD(wParam);
			/*获取发送事件*/
			int wmEvent = HIWORD(wParam);
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			/*开始重绘*/
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

			
			/*定义区域变量*/
			RECT rt;
			/*获取客户区范围*/
			GetClientRect(hWnd, &rt);
			/*绘制欢迎文本*/
			//DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			
			/*结束重绘*/
            EndPaint(hWnd, &ps);
        }
        break;
	/*销毁窗口*/
    case WM_DESTROY:
		/*发送退出消息*/
        PostQuitMessage(0);
        break;
	/*加入定时器处理函数*/
	case WM_TIMER:
		/*传入定时器类型为显示时间定时器*/
		if (wParam == WM_TIMER_CLOCK)
		{
			//定义tm结构的时间变量
			struct tm newdate;

			//定义time_t结构的时间变量
			time_t long_date;
			//获取时间
			time(&long_date);

			//将时间转换为本地时间
			localtime_s(&newdate, &long_date);

			memset(szTimerTitle, 0, sizeof(szTimerTitle));

			//strcpy_s(szTimerTitle, asctime(newdate));

			//char stTmp[100];
			asctime_s(szTimerTitle, &newdate);

			/*打印当前时间*/
			UpdateWindow(hWnd);
			/*显示当前窗口*/
		}
		break;
		/*默认情况，处理窗口消息*/
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
