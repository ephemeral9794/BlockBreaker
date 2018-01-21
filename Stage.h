//#include "Include.h"
//#include "Bar.h"
//#include "Ball.h"
//#include "Block.h"

#define V_BLOCKNUM 4
#define H_BLOCKNUM 14

class Stage : public Object {
private:
	int ox, oy, ow, oh;
	Ball* ball;
	Bar* bar;
	Block* block[V_BLOCKNUM][H_BLOCKNUM];
	int barw, barh;
	int ballw, ballh;
	int blkw, blkh;
	int bg;	// 背景画像ハンドル
	
	int sh;
	bool sflag;	// 音声再生中であるかのフラグ
	int volume;	// ボリューム
	int se;
	int sevolume;
public:
	virtual int Init(int x, int y, int w, int h) override;
	virtual int Update(BaseApplication* app) override;
	virtual int Draw() override;
	virtual void End() override;
	
	void SetVolume(int v ){ this->volume = v; }
	void SetSEVolume(int v ){ this->sevolume = v; }
private:
	void CheckHit();
};