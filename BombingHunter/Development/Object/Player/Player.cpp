#include "Player.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

// 静的メンバ変数宣言
float Player::player_x = 320.0f;
float Player::player_y = 150.0f;

// コンストラクタ
Player::Player() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

// デストラクタ
Player::~Player()
{
}

// 初期化処理
void Player::Initialize()
{
	// 画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Tri-pilot/1.png");
	animation[1] = LoadGraph("Resource/Images/Tri-pilot/2.png");

	// エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トリパイロットの画像がありません。");
	}

	// 向きの設定
	radian = 0.0;

	// 大きさの設定
	box_size = 64.0;

	// 初期画像の設定
	image = animation[0];
}

// 更新処理
void Player::Update()
{
	// 移動処理
	Movement();
	// アニメーション制御
	AnimeControl();

}

// 描画処理
void Player::Draw() const
{
	// プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, filp_flag);

	// デバッグ用
#if _DEBUG
	// 当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);
#endif

}

// 終了時処理
void Player::Finalize()
{
	// 使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

// 当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_obhect)
{
	// 当たった時の処理
}

// 移動処理
void Player::Movement()
{
	// 移動の速さ
	Vector2D veloctiy = 0.0f;

	// 左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		veloctiy.x += -1.0f;
		filp_flag = TRUE;
		player_x += veloctiy.x;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		veloctiy.x += 1.0f;
		filp_flag = FALSE;
		player_x += veloctiy.x;
	}
	else
	{
		veloctiy.x += 0.0f;
	}

	// 現在の位置座標に速さを加算する
	location += veloctiy;
}

// アニメーション制御
void Player::AnimeControl()
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
