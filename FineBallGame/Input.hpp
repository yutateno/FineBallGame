#pragma once
#include "DxLib.h"



// �L�[�{�[�h�̓��͏��
class KeyData
{
private:
	static int key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
	static char tmpKey[256];	// ���݂̃L�[�̓��͏�Ԃ��i�[����

public:
	static void UpDate();			// �L�[���͂̏�ԍX�V
	static int Get(int t_keyCode);	// �L�[���͏�Ԏ擾
	static bool CheckEnd();			// �����I��
};