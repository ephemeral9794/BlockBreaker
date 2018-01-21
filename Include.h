#pragma once

//#include <DxLib.h>

class BaseApplication {
protected:
	// キー入力制御
	int key[256];

	int UpdateKeyboardState(){
		char tmpKey[256]; // 現在のキーの入力状態を格納する
		GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
		for (int i = 0; i<256; i++) {
			if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
				key[i]++;     // 加算
			}
			else {              // 押されていなければ
				key[i] = 0;   // 0にする
			}
		}
		return 0;
	}

	// fps制御
	int start;
	int count;
	float fps;
	static const int Sample = 60;

	float Update(){
		if (count == 0){
			start = GetNowCount();
		}
		if (count == Sample){
			int time = GetNowCount();
			fps = 1000.0f / ((time-start)/(float)Sample);
			count = 0;
			start = time;
		}
		count++;

		return fps;
	}

	void Wait(){
		int time = GetNowCount() - start;
		int wait = (count*1000/60) - time;
		if (wait > 0){
			Sleep(wait);
		}
	}
public:
	BaseApplication(){
		ZeroMemory(key, sizeof(int) * 256);	// キー状態を初期化
		start = count = 0;
		fps = 0.0f;
	}
	virtual ~BaseApplication(){}

	enum {
		STATE_TITLE = 0,
		STATE_CONFIG,
		STATE_GAME,
		STATE_OVER,
		STATE_CLEAR,
		STATE_ALL = 99,
	};
	
	int GetKeyState(int code) { return key[code]; }
	virtual void ChangeState(int s) = 0;
	virtual void InitState(int s) = 0;
};

typedef struct tagMenu {
	int x, y;
	//LPTSTR name;
	int graph[2];
	int select;
	//int color;
} Menu;

class Object {
public:
	Object(){}
	virtual ~Object(){}

	virtual int Init(int x, int y, int w, int h) = 0;
	virtual int Update(BaseApplication* app) = 0;
	virtual int Draw() = 0;
	virtual void End() = 0;
};

typedef struct tagConfig {
	int bgm;
	int se;
} Config;
