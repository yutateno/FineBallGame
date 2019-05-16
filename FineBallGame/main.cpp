#include "Input.hpp"
#include <string>



// 受け渡し構造体
struct SVariable
{
	int count;

	int draw;

	bool upFlag;

	bool click;
};



// 描画
void Draw(SVariable (&t_playerA)[2], int& t_gameCount);



// プロセス
bool Process(SVariable(&t_playerA)[2], int& t_gameCount);



/*
メイン部分
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	// ログを出力させる
	SetOutApplicationLogValidFlag(TRUE);
#elif NDEBUG
	// ログを出力させない
	SetOutApplicationLogValidFlag(FALSE);
#endif

	SetWindowText("FineBallGame");		// window名の変更
	ChangeWindowMode(TRUE);				// ウィンドウモードに変更


	SetGraphMode(640, 480, 32);			// 画面サイズ設定

	// DxLibの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 裏画面描画


	SetBackgroundColor(255, 255, 255);


	SVariable player[2];
	ZeroMemory(player, sizeof(player));

	player[0].draw = LoadGraph("media\\player1.png");
	player[1].draw = LoadGraph("media\\player2.png");


	int gameCount = 0;


	int end = LoadGraph("media\\bakuhatsu.png");


	bool endFlag = false;


	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd())
	{
		KeyData::UpDate();						// キーボードの更新


		Draw(player, gameCount);


		if (endFlag = Process(player, gameCount))
		{
			DrawGraph(95, 52, end, false);

			DrawFormatString(300, 300, GetColor(0, 0, 0), "%s", player[0].count > player[1].count ? "左WIN!!!!!!!!" : player[0].count == player[1].count ? "DRAW" : "右WIN!!!!!!!!!!!!");
		}
	}


	// 解放
	DeleteGraph(end);
	DeleteGraph(player[1].draw);
	DeleteGraph(player[0].draw);

	// 後片付け
	InitGraph();
	DxLib_End();

	// プロジェクト終了
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