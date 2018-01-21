#pragma once
//#include "Include.h"

class Bar : public Object {
private:
	int bh;	// バー画像のハンドル
	int width, height;
	int ow, oh;
	int ox, oy;
	int x, y;
	int m;
public:
	virtual int Init(int x, int y, int w, int h) override;
	virtual int Update(BaseApplication* app) override;
	virtual int Draw() override;
	virtual void End() override;

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetX() const { return x + (width / 2); }
	int GetY() const { return y + (height / 2); }
};
