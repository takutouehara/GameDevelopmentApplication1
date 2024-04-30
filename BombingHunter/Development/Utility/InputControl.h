#pragma once

#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];
	static char old_key[D_KEYCODE_MAX];

public:
	static void Update();	// �X�V����

	static bool GetKey(int key_code);		// �����Ă��邩
	static bool GetKeyDown(int key_code);	// ��������
	static bool GetKeyUp(int key_code);		// ��������

private:
	// �L�[�R�[�h�͈̓`�F�b�N
	static bool CheckKeyCodeRange(int key_code);
};