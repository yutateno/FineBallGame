#include "Input.hpp"
#include <string>



// �󂯓n���\����
struct SVariable
{
	int count;

	int draw;

	bool upFlag;

	bool click;
};



// �`��
void Draw(SVariable (&t_playerA)[2], int& t_gameCount);



// �v���Z�X
bool Process(SVariable(&t_playerA)[2], int& t_gameCount);



/*
���C������
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	// ���O���o�͂�����
	SetOutApplicationLogValidFlag(TRUE);
#elif NDEBUG
	// ���O���o�͂����Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
#endif

	SetWindowText("FineBallGame");		// window���̕ύX
	ChangeWindowMode(TRUE);				// �E�B���h�E���[�h�ɕύX


	SetGraphMode(640, 480, 32);			// ��ʃT�C�Y�ݒ�

	// DxLib�̏�����
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// ����ʕ`��


	SetBackgroundColor(255, 255, 255);


	SVariable player[2];
	ZeroMemory(player, sizeof(player));

	player[0].draw = LoadGraph("media\\player1.png");
	player[1].draw = LoadGraph("media\\player2.png");


	int gameCount = 0;


	int end = LoadGraph("media\\bakuhatsu.png");


	bool endFlag = false;


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd())
	{
		KeyData::UpDate();						// �L�[�{�[�h�̍X�V


		Draw(player, gameCount);


		if (endFlag = Process(player, gameCount))
		{
			DrawGraph(95, 52, end, false);

			DrawFormatString(300, 300, GetColor(0, 0, 0), "%s", player[0].count > player[1].count ? "��WIN!!!!!!!!" : player[0].count == player[1].count ? "DRAW" : "�EWIN!!!!!!!!!!!!");
		}
	}


	// ���
	DeleteGraph(end);
	DeleteGraph(player[1].draw);
	DeleteGraph(player[0].draw);

	// ��Еt��
	InitGraph();
	DxLib_End();

	// �v���W�F�N�g�I��
	return 0;
}



/// -------------------------------------------------------------------------------------------------
void Draw(SVariable(&t_playerA)[2], int& t_gameCount)
{
	SVariable* playerA = &t_playerA[0];
	SVariable* playerB = &t_playerA[1];


	DrawGraph(64, 480 - 64 * 3, playerA->draw, false);
	DrawGraph(640 - 64 - 32, 480 - 64 * 3, playerB->draw, false);


	if (t_gameCount < 40)
	{
		DrawCircle(64 + 32, 144, playerA->count, GetColor(0, 0, 0), false);
		DrawCircle(640 - 64 - 32, 144, playerB->count, GetColor(0, 0, 0), false);
	}
	else if(t_gameCount < 70)
	{
		DrawCircle(64 + 32 + (t_gameCount - 40), 144 + (t_gameCount - 40), playerA->count, GetColor(0, 0, 0), false);
		DrawCircle(640 - 64 - 32 - (t_gameCount - 40), 144 + (t_gameCount - 40), playerB->count, GetColor(0, 0, 0), false);
	}

	
	if (t_gameCount >= 10)
	{
		DrawFormatString(64 - 32, 480 - ((64 * 3) / 2), GetColor(0, 0, 0), "%d", playerA->count);
		DrawFormatString(640 - 64 - 32 + 32, 480 - ((64 * 3) / 2), GetColor(0, 0, 0), "%d", playerB->count);
	}
}



/// -------------------------------------------------------------------------------------------------
bool Process(SVariable(&t_playerA)[2], int& t_gameCount)
{
	SVariable* playerA = &t_playerA[0];
	SVariable* playerB = &t_playerA[1];


	if (!playerA->click)
	{
		if (playerA->upFlag)
		{
			if (playerA->count++ > 70)
			{
				playerA->upFlag = false;
			}
		}
		else
		{
			if (playerA->count-- < 0)
			{
				playerA->upFlag = true;
			}
		}
	}


	if (!playerB->click)
	{
		if (playerB->upFlag)
		{
			if (playerB->count++ > 70)
			{
				playerB->upFlag = false;
			}
		}
		else
		{
			if (playerB->count-- < 0)
			{
				playerB->upFlag = true;
			}
		}
	}


	if (KeyData::Get(KEY_INPUT_Q) == 1)
	{
		playerA->click = true;
	}
	if (KeyData::Get(KEY_INPUT_P) == 1)
	{
		playerB->click = true;
	}


	if (playerA->click && playerB->click)
	{
		t_gameCount++;
	}


	if (t_gameCount >= 70)
	{
		return true;
	}


	return false;
}