//#include "Application.h"
#include "stdafx.h"

// �L�[�̓��͏�Ԃ��X�V����
/*int Application::UpdateKeyboardState() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}*/

int Application::Init(int w, int h, BOOL Windowed, LPTSTR lpText)
{
	this->Windowed = Windowed;
	this->lpText = lpText;

	ChangeWindowMode(Windowed);		// �E�B���h�E��
	SetGraphMode(w, h, 32);	// ��ʃT�C�Y�ύX
	width = w; height = h;

	if (lpText != NULL) {
		SetWindowText(lpText);	// �E�B���h�E�^�C�g���ݒ�
	}

	if (DxLib_Init() == -1) {	// DX���C�u����������
		return -1;	// ���������s
	}

	SetDrawScreen(DX_SCREEN_BACK);	// �o�b�N�o�b�t�@�ɕ`��
	SRand(GetNowCount());	// �����̏����l�i��j�ݒ�
	SetDrawMode(DX_DRAWMODE_BILINEAR);	// �o�C���j�A���

	title = new Title();
	if (title->Init(0, 0, w, h) != 0) {
		return -1;
	}
	game = new Game();
	if (game->Init(0, 0, w, h) != 0) {
		return -2;
	}
	end = new Ending();
	if (end->Init(0, 0, w, h) != 0){
		return -3;
	}

	// Config
	menu[0].x = 30;
	menu[0].y = 30;
	LoadDivGraph(_T("image\\bgmvolume.png"), 2, 2, 1, 196, 30, menu[0].graph);
	menu[0].select = 0;
	//menu[0].name = _T("BGM Volume");
	//menu[0].color = GetColor(0xff, 0xff, 0xff);
	menu[1].x = 30;
	menu[1].y = 65;
	LoadDivGraph(_T("image\\sevolume.png"), 2, 2, 1, 196, 30, menu[1].graph);
	menu[1].select = 0;
	//menu[1].name = _T("SE  Volume");
	//menu[1].color = GetColor(0xff, 0xff, 0xff);
	menu[2].x = 30;
	menu[2].y = 100;
	LoadDivGraph(_T("image\\exit.png"), 2, 2, 1, 75, 30, menu[2].graph);
	menu[2].select = 0;
	//menu[2].name = _T("Exit");
	//menu[2].color = GetColor(0xff, 0xff, 0xff);

	item = LoadGraph(_T("image\\item.png"));
	select = 0;
	c.bgm = 100;
	c.se  = 100;
	
	// Config�O������
	bool create = false;
	HANDLE file = CreateFile(_T("config.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE){
		file = CreateFile(_T("config.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		create = true;
		if (file == INVALID_HANDLE_VALUE){
			return -4;
		}
	}

	if (!create){	// config.dat������ꍇ
		DWORD dwLong;
		ReadFile(file, &c, sizeof(Config), &dwLong, NULL);
	}

	CloseHandle(file);

	return 0;
}

int Application::Run()
{
	// �Q�[�����[�v
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && this->UpdateKeyboardState() == 0) {
		this->Update();

		if (this->GetKeyState(KEY_INPUT_ESCAPE)) {	// ESC�L�[�ŏI��
			break;
		}
		switch (state) {
		case STATE_TITLE:
			title->SetVolume(c.bgm);
			title->SetSEVolume(c.se);
			title->Update(this);
			title->Draw();
			break;
		case STATE_CONFIG:
			//config->Update(this);
			//config->Draw();
			//volume = config->GetVolume();
			//sevolume = config->GetSEVolume();
			this->ConfigUpdate();
			this->ConfigDraw();
			break;
		case STATE_GAME:
			game->SetVolume(c.bgm);
			game->SetSEVolume(c.se);
			game->Update(this);
			game->Draw();
			break;
		case STATE_OVER:
			end->SetFlag(false);
			end->SetVolume(c.bgm);
			end->Update(this);
			end->Draw();
			break;
		case STATE_CLEAR:
			end->SetFlag(true);
			end->SetVolume(c.bgm);
			end->Update(this);
			end->Draw();
			break;
		default:
			return -1;
		}

		if (ScreenFlip() != 0) {
			break;
		}

		this->Wait();
	}

	return 0;
}

void Application::End()
{
	DxLib_End();
	if (title) {
		title->End();
		delete title;
		title = NULL;
	}
	if (game) {
		game->End();
		delete game;
		game = NULL;
	}
	if (end) {
		end->End();
		delete end;
		end = NULL;
	}

	// Config�����o��
	HANDLE file = CreateFile(_T("config.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwLong;
	WriteFile(file, &c, sizeof(Config), &dwLong, NULL);

	CloseHandle(file);
}

int Application::ConfigUpdate()
{
	if (this->GetKeyState(KEY_INPUT_DOWN) == 1) {
		select = (select + 1) % 3;
	}
	if (this->GetKeyState(KEY_INPUT_UP) == 1) {
		select = (select + 2) % 3;
	}
	for (int i = 0; i < 3; i++) {
		if (select == i) {
			menu[i].select = 1;
		}
		else {
			menu[i].select = 0;
		}
	}
	if (select == 0){
		if (this->GetKeyState(KEY_INPUT_RIGHT) == 1){
			if (c.bgm < 100) {
				c.bgm = c.bgm + 10;
			}
		}
		if (this->GetKeyState(KEY_INPUT_LEFT) == 1){
			if (c.bgm > 0) {
				c.bgm = c.bgm - 10;
			}
		}
	}
	if (select == 1){
		if (this->GetKeyState(KEY_INPUT_RIGHT) == 1){
			if (c.se < 100) {
				c.se = c.se + 10;
			}
		}
		if (this->GetKeyState(KEY_INPUT_LEFT) == 1){
			if (c.se > 0) {
				c.se = c.se - 10;
			}
		}
	}
	if (select == 2 && this->GetKeyState(KEY_INPUT_RETURN) == 1){
		this->ChangeState(BaseApplication::STATE_TITLE);
		return 1;
	}

	return 0;
}

int Application::ConfigDraw()
{
	for (int i=0;i < 3; i++){
		//DrawString(menu[i].x, menu[i].y, menu[i].name, menu[i].color);	
		DrawGraph(menu[i].x, menu[i].y, menu[i].graph[menu[i].select], TRUE);
	}

	int n = c.bgm / 10;
	for (int i=0;i<n;i++){
		//DrawString(200 + (30 * i), 30, "��", GetColor(0xff,0xff, 0xff));
		DrawGraph(230 + (30 * i), 30, item, TRUE);
	}

	n = c.se / 10;
	for (int i=0;i<n;i++){
		//DrawString(200 + (30 * i), 65, "��", GetColor(0xff,0xff, 0xff));
		DrawGraph(230 + (30 * i), 65, item, TRUE);
	}

	return 0;
}
