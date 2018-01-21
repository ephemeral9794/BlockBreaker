//#include "Application.h"
#include "stdafx.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	Application* app = new Application();

	if (app->Init(640, 480, TRUE, _T("Block Breaker")) != 0) {
		MessageBox(NULL, _T("�Q�[���̏������Ɏ��s���܂����B"), _T("Application Error"), MB_OK);
		app->End();
		delete app;
		app = NULL;
		return -1;
	}

	int result = app->Run();
	if (result != 0) {
		MessageBox(NULL, _T("�Q�[�����쒆�ɃG���[���������܂����B"), _T("Application Error"), MB_OK);
	}

	app->End();

	delete app;
	app = NULL;

	return result;
}