#pragma once
//#include "Include.h"

class Ball : public Object {
private:
	int bh;	// �{�[���摜�̃n���h��
	int width, height;	// �{�[���̍����A��
	int ow, oh;	// ��ʂ̍����A��
	int ox, oy;	// ��ʂ̌��_���W
	int x, y;	// �{�[���̍��W
	int mx, my;	// �{�[���̈ړ���
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
