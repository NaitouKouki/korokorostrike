#pragma once

class GraphicsEngine;
extern HWND			g_hWnd ;				// ウィンドウハンドル

// ゲームの初期化
void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
// ウィンドウメッセージのディスパッチ。falseを返した場合、ゲーム終了。
bool DispatchWindowMessage();