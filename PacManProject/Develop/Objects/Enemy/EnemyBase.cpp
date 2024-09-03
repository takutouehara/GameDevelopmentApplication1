#include "EnemyBase.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

EnemyBase::EnemyBase() : 
	direction(),
	animation_time(0.0f),
	animation_count(0)
{
	 
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Initialize()
{

}

void EnemyBase::Update(float delta_second)
{

}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void EnemyBase::Finalize()
{

}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{

}
