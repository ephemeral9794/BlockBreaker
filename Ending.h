//#include "Include.h"

class Ending : public Object {
private:
	//int count;
	bool flag;	// �N���A������true, �Q�[���I�[�o�[�Ȃ�false
	int ow, oh;
	int ox, oy;
	int sh;	// BGM�̃n���h��
	int volume;	// BGM�̃{�����[��
	int bh1, bh2;
	bool sflag;
public:
	Ending() : volume(100), sflag(false), sh(-1), bh1(-1),bh2(-1) {}
	virtual ~Ending() {}

	virtual int Init(int x, int y, int w, int h) override;
	virtual int Update(BaseApplication* app) override;
	virtual int Draw() override;
	virtual void End() override;

	void SetFlag(bool f){ this->flag = f; }
	void SetVolume(int v){ this->volume = v; }
};