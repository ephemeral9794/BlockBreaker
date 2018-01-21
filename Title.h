#pragma once
//#include "Include.h"

#define MENU_NUM 2

class Title : public Object{
private:
	int th;	// タイトル画像のハンドル
	int ph;	// タイトル画像２のハンドル
	int sh;	// 音声のハンドル
	int se;	// SE1
	int count;
	bool dflag;	// 点滅用フラグ

	bool sflag;	// 音声再生中であるかのフラグ
	int volume;	// ボリューム
	int sevolume;	// SEのボリューム

	Menu menu[MENU_NUM];	// メニューパーツ
	int select;	// 選択されているメニュー
	bool enter;	// メニュー開始フラグ
public:
	Title() : th(-1), ph(-1), sh(-1), count(0), dflag(false), sflag(false), select(0), enter(false), volume(100), sevolume(100) {}
	virtual ~Title(){}

	virtual int Init(int x, int y, int w, int h) override;
	virtual int Update(BaseApplication* app) override;
	virtual int Draw() override;
	virtual void End() override;

	void SetVolume(int v) { this->volume = v; }
	void SetSEVolume(int v) { this->sevolume = v; }
};
