#include "GoldEnemy.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Result.h"
#include "DxLib.h"

// コンストラクタ
GoldEnemy::GoldEnemy() :animation_count(0), direction(0.0f)
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
	box_size = 64.0;

	// 初期画像の設定
	image = animation[0];

	// 初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);
}

// 更新処理
void GoldEnemy::Update()
{
	// 移動処理
	Movement();

	// アニメーション制御
	AnimeControl();
}

// 描画処理
void GoldEnemy::Draw() const
{
	// 画像反転
	int flip_flag = FALSE;

	// 進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	// エネミー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	// 親クラスの描画処理を呼び出す
	__super::Draw();
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
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	// 使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

	// スコア加算
	//Result::score += 3000;
}

// 移動処理
void GoldEnemy::Movement()
{
	// 画面端に到達したら進行方向を反転する
	if (((location.x + direction.x) < box_size.x) || (960.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) || (720.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
	// 進行方向に向かって位置座標を変更する
	location += direction;
}

// アニメーション制御処理
void GoldEnemy::AnimeControl()
{
	// フレームカウントを加算する
	animation_count++;

	// 30フレーム目に到達したら
	if (animation_count >= 30)
	{
		// カウントのリセット
		animation_count = 0;
	}
}
