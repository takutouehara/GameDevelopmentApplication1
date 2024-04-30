#include "GoldEnemy.h"
#include "DxLib.h"

// コンストラクタ
GoldEnemy::GoldEnemy() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
}

// デストラクタ
GoldEnemy::~GoldEnemy()
{
}

// 初期化処理
void GoldEnemy::Initialize()
{
	// 画像の読み込み
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");

	// エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ダイヤテキの画像がありません。");
	}

	// 向きの設定
	radian = 0.0;

	// 大きさの設定
	scale = 64.0;

	// 初期画像の設定
	image = animation[0];
}

// 更新処理
void GoldEnemy::Update()
{
	AnimeControl();	// アニメーション制御
}

// 描画処理
void GoldEnemy::Draw() const
{
	// エネミー画像の描画
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);
}

// 終了時処理
void GoldEnemy::Finalize()
{
	// 使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
}

// 当たり判定通知処理
void GoldEnemy::OnHitCollision(GameObject* hit_obhect)
{
	// 当たった時の処理
}

// アニメーション制御処理
void GoldEnemy::AnimeControl()
{
	// フレームカウントを加算する
	animation_count++;

	// 60フレーム目に到達したら
	if (animation_count >= 60)
	{
		// カウントのリセット
		animation_count = 0;

		/*
		// 画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
		*/
		if (image == animation[0])
		{
			for (int i = 0; i < 5; i++)
			{
				image = animation[i];
			}
		}
		else if (image == animation[4])
		{
			image = animation[0];
		}
		
	}
}
