#include "SHADOWBLINKY.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "EnemyBase.h"
#include "DxLib.h"

SHADOWBLINKY::SHADOWBLINKY() :
	move_animation(),
	eyes_animation(),
	enemy_state(eEnemyState::IDOL),
	old_location(),
	velocity(0.0f)
{

}

SHADOWBLINKY::~SHADOWBLINKY()
{

}

void SHADOWBLINKY::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation =  rm->GetImages("Resource/Images/monster.png", 12, 12, 1, 32, 32);
	eyes_animation = rm->GetImages("Resource/Images/eyes.png", 11, 11, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

}

void SHADOWBLINKY::Update(float delta_second)
{
	EnemyBase* enemy_base = new EnemyBase;

	// プレイヤー状態によって、動作を変える
	switch (enemy_state)
	{
	case eEnemyState::IDOL:
		// 画像の設定
		image = move_animation[9];
		break;
	case eEnemyState::MOVE:
		// 移動処理
		Movement(delta_second);
		// アニメーション制御
		AnimationControl(delta_second);
		break;
	case eEnemyState::IZIKE:
		break;
	case eEnemyState::EYE:
		break;
	default:
		break;
	}
}

void SHADOWBLINKY::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void SHADOWBLINKY::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eyes_animation.clear();
}

void SHADOWBLINKY::Movement(float delta_second)
{

}

void SHADOWBLINKY::AnimationControl(float delta_second)
{

}

eEnemyState SHADOWBLINKY::GetEnamyState() const
{
	return eEnemyState();
}
