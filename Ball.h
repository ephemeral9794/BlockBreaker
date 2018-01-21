#pragma once
//#include "Include.h"

class Ball : public Object {
private:
	int bh;	// ボール画像のハンドル
	int width, height;	// ボールの高さ、幅
	int ow, oh;	// 画面の高さ、幅
	int ox, oy;	// 画面の原点座標
	int x, y;	// ボールの座標
	int mx, my;	// ボールの移動量
public:
	virtual int Init(int x, int y, int w, int h) override;
	virtual int Update(BaseApplication* app) override;
	virtual int Draw() override;
	virtual void End() override;

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetX() const { return x + (width / 2); }
	int GetY() const { return y + (height / 2); }
	int GetMoveX() const { return mx; }
	int GetMoveY() const { return my; }
	void SetMoveX(int mx) { this->mx = mx; }
	void SetMoveY(int my) { this->my = my; }
};
