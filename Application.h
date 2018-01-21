#pragma once
//#include "Include.h"
//#include "Title.h"
//#include "Game.h"
//#include "Ending.h"
//#include "Config.h"

class Application : public BaseApplication{
private:
	//int key[256];
	int state;
	int width, height;
	BOOL Windowed;
	LPTSTR lpText;
	Title* title;
	Game* game;
	Ending* end;
	
	Menu menu[3];
	int select;
	int item;
	Config c;
private:
	//int UpdateKeyboardState();
public:
	Application() : width(0), height(0){
		//ZeroMemory(key, sizeof(int) * 256);	// ƒL[ó‘Ô‚ð‰Šú‰»
		state = STATE_TITLE;
		title = NULL;
		game = NULL;
		end = NULL;
	}
	~Application(){}

	int Init(int w, int h, BOOL Windowed = TRUE, LPTSTR lpText = _T("Block Breaker"));
	int Run();
	void End();

	//virtual int GetKeyState(int code) override { return key[code]; }

	// State
	virtual void ChangeState(int s) override { this->state = s; }
	virtual void InitState(int s) override { 
		switch(s){
		case STATE_TITLE:
			title->Init(0, 0, width, height);
			break;
		case STATE_GAME:
			game->Init(0, 0, width, height);
			break;
		case STATE_OVER:
			end->Init(0, 0, width, height);
			end->SetFlag(false);
			break;
		case STATE_CLEAR:
			end->Init(0, 0, width, height);
			end->SetFlag(true);
			break;
		case STATE_ALL:
		default:
			title->Init(0, 0, width, height);
			game->Init(0, 0, width, height);
			end->Init(0, 0, width, height);
		}
	}

	// Config
	int ConfigUpdate();
	int ConfigDraw();
};
