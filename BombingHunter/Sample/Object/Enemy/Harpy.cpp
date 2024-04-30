#include "Harpy.h"
#include "DxLib.h"

// コンストラクタ
Harpy::Harpy() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

// デストラクタ
Harpy::~Harpy()
{
}

// 初期化処理
void Harpy::Initialize()
{
	// 画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
	animation[1] = LoadGraph("Resource/Images/Harpy/2.png");

	// エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハーピーの画像がありません。");
	}

	// 向きの設定
	radian = 0.0;

	// 大きさの設定
	scale = 64.0;

	// 初期画像の設定
	image = animation[0];
}

// 更新処理
void Harpy::Update()
{
	AnimeControl();	// アニメーション制御
}

// 描画処理
void Harpy::Draw() const
{
	// エネミー画像の描画
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);
}

// 終了時処理
void Harpy::Finalize()
{
	// 使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

// 当たり判定通知処理
void Harpy::OnHitCollision(GameObject* hit_obhect)
{
	// 当たった時の処理
}

// アニメーション制御処理
void Harpy::AnimeControl()
{
	// フレームカウントを加算する
	animation_count++;

	// 60フレーム目に到達したら
	if (animation_count >= 60)
	{
		// カウントのリセット
		animation_count = 0;

		// 画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
