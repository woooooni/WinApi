﻿// DawnProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DawnProject.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //의미없음.(사용하지 않는 매개변수임을 명시.)
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DAWNPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DAWNPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DAWNPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DAWNPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, L"Hello", WS_OVERLAPPEDWINDOW,
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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


POINT g_ptObjectPos = { 500,300 };
POINT g_ptObjectScale = { 100, 100 };

#include<vector>
using std::vector;

bool isLBtnDown = false;

struct tObjInfo 
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;

POINT g_leftTop;
POINT g_rightBottom;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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

    case WM_PAINT: //무효화 영역이 발생한 경우.
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hWnd, &ps); // DeviceContext(그리기와 관련.)

            //1. 펜, 브러쉬 생성
            HPEN hRedPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
            HBRUSH hRedBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);


            //2. 펜, 브러쉬 설정
            // SelectObejct()
            // 내가 만든 Pen 혹은 Brush를 HDC에 설정하고, 
            // 이전에 사용하던 Pen, Brush를 void형 포인터로 반환.
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); 
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hRedBrush);

            if (isLBtnDown) {
                Rectangle(hdc,
                    g_leftTop.x, g_leftTop.y,
                    g_rightBottom.x, g_rightBottom.y);
            }

            for (int i = 0; i < g_vecInfo.size(); i++) 
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2,
                    g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }
            
            
            //4. 다시 default로 되돌리기.
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            //5. 만들었던 펜, 브러쉬 삭제.
            DeleteObject(hRedPen);
            DeleteObject(hRedBrush);
            
            EndPaint(hWnd, &ps);
        }
        break;
    
    case WM_KEYDOWN: 
    {
        //키 입력
        switch (wParam)
        {
        case VK_UP:
            //g_ptObjectPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_DOWN:
            //g_ptObjectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            //g_ptObjectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            //g_ptObjectPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        default:
            break;
        }

    }
        break;
    
    //마우스 왼쪽 클릭
    case WM_LBUTTONDOWN:
    {
        g_leftTop.x = LOWORD(lParam);
        g_leftTop.y = HIWORD(lParam);
        isLBtnDown = true;
    }
        break;
    case WM_MOUSEMOVE:
    {
        g_rightBottom.x = LOWORD(lParam);
        g_rightBottom.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_LBUTTONUP:
    {
        tObjInfo info = {};

        info.g_ptObjPos.x = (g_leftTop.x + g_rightBottom.x) / 2;
        info.g_ptObjPos.y = (g_leftTop.y + g_rightBottom.y) / 2;

        info.g_ptObjScale.x = abs(g_leftTop.x - g_rightBottom.x);
        info.g_ptObjScale.y = abs(g_leftTop.y - g_rightBottom.y);

        g_vecInfo.push_back(info);

        isLBtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
