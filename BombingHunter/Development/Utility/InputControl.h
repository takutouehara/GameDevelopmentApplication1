#pragma once

#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];
	static char old_key[D_KEYCODE_MAX];

public:
	static void Update();	// 更新処理

	static bool GetKey(int key_code);		// 押しているか
	static bool GetKeyDown(int key_code);	// 押したか
	static bool GetKeyUp(int key_code);		// 離したか

private:
	// キーコード範囲チェック
	static bool CheckKeyCodeRange(int key_code);
};