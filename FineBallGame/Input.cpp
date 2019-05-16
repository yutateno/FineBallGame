#include "Input.hpp"



//////////////////////////////////////////////�L�[�{�[�h////////////////////////////////////////////////////

int KeyData::key[256];
char KeyData::tmpKey[256];


/// ------------------------------------------------------------------------------------------------------------
void KeyData::UpDate()
{
	GetHitKeyStateAll(KeyData::tmpKey);	// �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;
		}
		// �L�[�������ꂽ�u��
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1;
		}
		// �A�N�V�������Ȃ�
		else
		{
			KeyData::key[i] = 0;
		}
	}
}



/// ------------------------------------------------------------------------------------------------------------
bool KeyData::CheckEnd()
{
	return KeyData::key[KEY_INPUT_ESCAPE] <= 0;
}



/// ------------------------------------------------------------------------------------------------------------
int KeyData::Get(int t_keyCode)
{
	return KeyData::key[t_keyCode];
}