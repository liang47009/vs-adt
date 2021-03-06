#include "GLES3Renderer.h"

#ifdef WIN32
#include "win_graphdevice.h"
#else

#endif // WIN32
#ifdef WIN32
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		case WM_CLOSE:
		DestroyWindow(hwnd);
		// ��ֹϵͳ�Զ��رմ���
		return 0;
		case WM_DESTROY:
		PostQuitMessage(0);
		break;

#ifdef AUTO_SIZE
		case WM_SIZE:
		{
			RECT rcClient = {0, 0, 1, 1};
			GetClientRect(hwnd, &rcClient);
			int iWidth = rcClient.right - rcClient.left;
			int iHeight = rcClient.bottom - rcClient.top;

			//
			if (g_pWorld)
			{
				g_pWorld->SetWidth(iWidth);
				g_pWorld->SetHeight(iHeight);
			}

			//
			IRender* pRender = (IRender*)g_pCorePtr->GetInterface("Render");
			if (pRender)
			{
				pRender->SetDeviceSize(iWidth, iHeight);
				pRender->ResetDevice();
			}

			//
			Gui* pGui = (Gui*)g_pCorePtr->LookupEntity("Gui");
			if (pGui != NULL)
			{
				float fScale = 1.0f;
				float ui_ratio = (float)iWidth / (float)iHeight;
				if (ui_ratio>1.3f && ui_ratio<1.4f)
				{
					// 4 / 3 ����
					fScale = 0.85f;
				}
				else if (ui_ratio>1.7f && ui_ratio<1.8f)
				{
					// 16 / 9 ����
					fScale = 1.0f;
				}
				fScale *= iHeight / float(UI_HEIGHT);

				pGui->SetScaleEnable(fScale != 1.0f);
				pGui->SetScaleRatio(fScale);
			}
		}
		break;
#endif
		default:
		break;
	}

	// ���F10��Alt����������
	if (iMsg == WM_SYSKEYUP && (wParam == VK_MENU || wParam == VK_F10))
	{
		return 0L;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

//
int WinMainProc(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	GLES3Renderer demo;
	CGraphDevice graphedevice;

	DWORD FACE_WIDTH = 480;
	DWORD FACE_HEIGHT = 480;

	// ��С��ջ
	if (true)
	{
		// ����Windows����
		WNDCLASSEX wndclass;

		wndclass.cbSize = sizeof(wndclass);
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;//sizeof(WORD);
		wndclass.hInstance = hInstance;
		wndclass.hIcon = NULL;
		wndclass.hCursor = LoadCursor(hInstance, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = TEXT("demo");
		wndclass.hIconSm = NULL;

		RegisterClassEx(&wndclass);
		RECT winRect;
		SetRect(&winRect, 0, 0, FACE_WIDTH, FACE_HEIGHT);
		AdjustWindowRectEx(&winRect, WS_CAPTION | WS_SYSMENU, false, 0);

		int x = -winRect.left;
		winRect.left += x;
		winRect.right += x;
		int y = -winRect.top;
		winRect.top += y;
		winRect.bottom += y;

#ifdef AUTO_SIZE
		HWND hwnd = CreateWindow(TEXT("demo"), TEXT("demo"), WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX,
				(GetSystemMetrics(SM_CXSCREEN) - FACE_WIDTH) / 2,
				(GetSystemMetrics(SM_CYSCREEN) - FACE_HEIGHT) / 2,
				winRect.right - winRect.left, winRect.bottom - winRect.top, NULL, NULL, hInstance, NULL);
#else
#ifdef NO_CAPTION
		HWND hwnd = CreateWindow(TEXT("demo"), TEXT("demo"), WS_VISIBLE | WS_POPUP,
				0, 0,
				winRect.right - winRect.left, winRect.bottom - winRect.top, NULL, NULL, hInstance, NULL);
#else
		HWND hwnd = CreateWindow(TEXT("demo"), TEXT("demo"), WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
				(GetSystemMetrics(SM_CXSCREEN) - FACE_WIDTH) / 2,
				(GetSystemMetrics(SM_CYSCREEN) - FACE_HEIGHT) / 2,
				winRect.right - winRect.left, winRect.bottom - winRect.top, NULL, NULL, hInstance, NULL);
#endif
#endif
		//InitSnailEditor(hInstance, hwnd);

		//#ifdef FULL_SCREEN
		//		LONG        style = GetWindowLong(hwnd, GWL_STYLE);
		//		style &= ~(WS_DLGFRAME | WS_THICKFRAME);
		//		SetWindowLong(hwnd, GWL_STYLE, style);
		//
		//		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		//#else
		ShowWindow(hwnd, SW_SHOW);
		//#endif

		UpdateWindow(hwnd);
		::GetClientRect(hwnd, &winRect);
		graphedevice.InitDevice(hwnd);
	}
	// ����Ϣѭ��
	MSG msg;

	demo.Init(FACE_WIDTH, FACE_HEIGHT);

	for (;;)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				graphedevice.ShutDevice();
				return 1;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}
		}
		graphedevice.Present();
		demo.Render();
	}
	graphedevice.ShutDevice();
	return 1;
}

//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int iCmdShow)
{
	//
//	CrAutoInstallHelper ar("taiji", MiniDumpWithFullMemory);
#ifdef _DEBUG
	// Enable memory-leak reports
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
	//_CrtSetBreakAlloc(279);

	_CrtDumpMemoryLeaks();
#endif
	//if (IsDebuggerPresent() == FALSE)
	//{
	//	//InitMiniDump();
	//}

	//DumpMan dumpMan;
	//dumpMan.Create();

	return WinMainProc(hInstance, hPrevInstance, lpCmdLine, iCmdShow);
}
#else 

#if defined(ANDROID) || defined(__ANDROID__)
#include <jni.h>
#include <android/log.h>
#include <android/asset_manager_jni.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "mufeng", __VA_ARGS__))

#include "GLES3Renderer.h"

GLES3Renderer render;
AAssetManager* gAssetMgr;
extern "C" {

JNIEXPORT void JNICALL Java_com_yunfeng_mufeng_GL2JNILib_init(JNIEnv *,
		jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_yunfeng_mufeng_GL2JNILib_step(JNIEnv *,
		jobject);
JNIEXPORT void JNICALL Java_com_yunfeng_mufeng_GL2JNILib_created(JNIEnv *,
		jobject, jobject);
}
;

JNIEXPORT void JNICALL Java_com_yunfeng_mufeng_GL2JNILib_init(JNIEnv *, jobject,
		jint width, jint height) {
	LOGI("width: %d, height: %d", width, height);
	render.Init(width, height);
}

JNIEXPORT void JNICALL Java_com_yunfeng_mufeng_GL2JNILib_step(JNIEnv *,
		jobject) {
	render.Render();
}

JNIEXPORT void JNICALL Java_com_yunfeng_mufeng_GL2JNILib_created(JNIEnv *env,
		jobject, jobject assetManager) {
	gAssetMgr = AAssetManager_fromJava(env, assetManager);
	shader::mAssetManager = gAssetMgr;
//	created(assetMgr);
}

#endif

#endif
