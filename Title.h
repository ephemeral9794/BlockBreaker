#pragma once
//#include "Include.h"

#define MENU_NUM 2

class Title : public Object{
private:
	int th;	// �^�C�g���摜�̃n���h��
	int ph;	// �^�C�g���摜�Q�̃n���h��
	int sh;	// �����̃n���h��
	int se;	// SE1
	int count;
	bool dflag;	// �_�ŗp�t���O

	bool sflag;	// �����Đ����ł��邩�̃t���O
	int volume;	// �{�����[��
	int sevolume;	// SE�̃{�����[��

	Menu menu[MENU_NUM];	// ���j���[�p�[�c
	int select;	// �I������Ă��郁�j���[
	bool enter;	// ���j���[�J�n�t���O
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
