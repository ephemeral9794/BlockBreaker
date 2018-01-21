//#include "Include.h"

class Block : public Object {
private:
	//int bh;	// �u���b�N�摜�̃n���h��
	int bh[8];	// �u���b�N�摜�̃n���h��x8
	int width, height;	// �u���b�N��̑傫��
	int x, y;
	int kind;	// �u���b�N�F�̎��
	bool flag;	// �u���b�N�����݂��邩�̃t���O
	int alpha;	// �A���t�@�l
public:
	enum {
		BLOCK_RED = 0,	// ��
		BLOCK_YELLOW,	// ��
		BLOCK_YGREEN,	// ����
		BLOCK_GREEN,	// ��
		BLOCK_PINK,		// �s���N
		BLOCK_PURPLE,	// ��
		BLOCK_BLUE,		// ��
		BLOCK_GRAY,		// �D
	};

	virtual int Init(int x, int y, int w, int h) override;
	virtual int Update(BaseApplication* app) override;
	virtual int Draw() override;
	virtual void End() override;

	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }
	void SetPosition(int x, int y) { this->SetX(x); this->SetY(y); }
	void SetKind(int k) { this->kind = k; }
	void SetFlag(bool f) { this->flag = f; }
	int GetX() const { return x + (width / 2); }
	int GetY() const { return y + (height / 2); }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetKind() const { return kind; }
	bool GetFlag() const { return flag; }
};