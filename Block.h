//#include "Include.h"

class Block : public Object {
private:
	//int bh;	// ブロック画像のハンドル
	int bh[8];	// ブロック画像のハンドルx8
	int width, height;	// ブロック一個の大きさ
	int x, y;
	int kind;	// ブロック色の種類
	bool flag;	// ブロックが存在するかのフラグ
	int alpha;	// アルファ値
public:
	enum {
		BLOCK_RED = 0,	// 赤
		BLOCK_YELLOW,	// 黄
		BLOCK_YGREEN,	// 黄緑
		BLOCK_GREEN,	// 緑
		BLOCK_PINK,		// ピンク
		BLOCK_PURPLE,	// 紫
		BLOCK_BLUE,		// 青
		BLOCK_GRAY,		// 灰
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