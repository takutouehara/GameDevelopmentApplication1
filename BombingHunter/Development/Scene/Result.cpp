#include "Result.h"
#include "DxLib.h"

// 静的メンバ変数宣言
int Result::score = 0;
int Result::highscore ;

// コンストラクタ
Result::Result() :animation_count(0), number_count_tp(1), number_count_op(0)
{
	for (int i = 0; i < 3; i++)
	{
		image[i] = NULL;
	}
	for (int j = 0; j < 10; j++)
	{
		number[j] = NULL;
	}
}

// デストラクタ
Result::~Result()
{
}

// 初期化処理
void Result::Initialize()
{
	// 格納処理呼び出し
	Storage();
}

// 更新処理
void Result::Update()
{
	// 時間計測
	TimerControl();
}

// 描画処理
void Result::Draw() const
{
	// 時計の描画
	DrawGraph(10, 662, image[0], TRUE);
	// 時間の描画
	DrawRotaGraphF(100, 690, 2.5, 0.0, number[number_count_tp], TRUE);
	DrawRotaGraphF(140, 690, 2.5, 0.0, number[number_count_op], TRUE);

	// スコアの描画
	DrawRotaGraphF(300, 690, 2.5, 0.0, image[1], TRUE);
	DrawFormatString(450, 690, GetColor(255, 0, 0), "%d", score);

	// ハイスコアの描画
	DrawRotaGraphF(650, 690, 2.5, 0.0, image[2], TRUE);
	DrawFormatString(800, 690, GetColor(255, 0, 0), "%d", highscore);
}

// 終了時処理
void Result::Finalize()
{
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(image[i]);
	}
	for (int j = 0; j < 10; j++)
	{
		DeleteGraph(number[j]);
	}

	//highscore = score;
}

// 格納処理
void Result::Storage()
{
	image[0] = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	image[1] = LoadGraph("Resource/Images/Score/font-21.png");
	image[2] = LoadGraph("Resource/Images/Score/hs.png");
	number[0] = LoadGraph("Resource/Images/Score/0.png");
	number[1] = LoadGraph("Resource/Images/Score/1.png");
	number[2] = LoadGraph("Resource/Images/Score/2.png");
	number[3] = LoadGraph("Resource/Images/Score/3.png");
	number[4] = LoadGraph("Resource/Images/Score/4.png");
	number[5] = LoadGraph("Resource/Images/Score/5.png");
	number[6] = LoadGraph("Resource/Images/Score/6.png");
	number[7] = LoadGraph("Resource/Images/Score/7.png");
	number[8] = LoadGraph("Resource/Images/Score/8.png");
	number[9] = LoadGraph("Resource/Images/Score/9.png");
}

// 時間計測処理
void Result::TimerControl()
{
	// フレームカウントを加算する
	animation_count++;

	//110フレーム目に到達したら
	if (animation_count >= 110)
	{
		// カウントのリセット
		animation_count = 0;

		number_count_op--;
		
		if (number_count_op < 0)
		{
			number_count_op = 9;

			if (number_count_tp != 0)
			{
				number_count_tp--;
			}
		}
		else if (number_count_op == 0)
		{
			number_count_op = 0;
		}
		
	}
}
