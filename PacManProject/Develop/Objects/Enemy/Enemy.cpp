#include "Enemy.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "../Food/Food.h"

#define D_PLAYER_SPEED	(50.0f)

Enemy::Enemy() :
	move_animation(),
	izike_animation(),
	eyes_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::MOVE),
	animation_time(0.0f),
	animation_count(0),
	old_panel(ePanelID::NONE)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyes_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
	izike_animation = rm->GetImages("Resource/Images/.png", 12, 12, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

void Enemy::Update(float delta_second)
{
	// プレイヤー状態によって、動作を変える
	switch (enemy_state)
	{
	case eEnemyState::IDLE:
		// 画像の設定
		image = move_animation[9];
		break;
	case eEnemyState::MOVE:
		// 移動処理
		Movement(delta_second);
		// アニメーション制御
		AnimationControl(delta_second);
		break;
	case eEnemyState::EYE:
		// 撤退中のアニメーション
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			// 復活させる
			if (animation_count >= eyes_animation.size())
			{
				enemy_state = eEnemyState::IDLE;
				animation_count = 0;
			}
		}
		image = eyes_animation[animation_count];
		break;
	case eEnemyState::IZIKE:

		break;
	default:
		break;
	}
}

void Enemy::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void Enemy::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eyes_animation.clear();
	izike_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Enemy::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Enemyからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}

	// 当たったオブジェクトが敵だったら
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::EYE;
	}
}

/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
eEnemyState Enemy::GetEnemyState() const
{
	return enemy_state;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Enemy::Movement(float delta_second)
{
	// 入力状態の取得
	InputManager* input = InputManager::GetInstance();

	// 現在パネルの状態を確認
	ePanelID panel = StageData::GetPanelData(location);

	// 前回座標の更新
	old_location = location;

	// 前回パネルの更新
	old_panel = panel;

	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_PLAYER_SPEED * delta_second;

	// 画面外に行ったら、反対側にワープさせる
	if (location.x < 0.0f)
	{
		old_location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		old_location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Enemy::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
	}
}
