#pragma once

#include "../GameObject.h"

class EnemyBase : public GameObject
{
	// 進行方向状態
	enum eDirectionState
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};
	
public:
	eDirectionState direction;			// 進行方向状態
	float			animation_time;		// アニメーション時間
	int				animation_count;	// アニメーション添字

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;									// 初期化処理
	virtual void Update(float delta_second) override;					// 更新処理
	virtual void Draw(const Vector2D& screen_offset) const override;	// 描画処理
	virtual void Finalize() override;									// 終了時処理

	/// <summary>
	/// 当たり判定通知
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	
};