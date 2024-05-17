#pragma once

#include "../GameObject.h"

class EnemyBullet:public GameObject
{
private:
	int animation[4];		// アニメーション画像
	int animation_count;	// アニメーション時間
	Vector2D direction;		// 方向

public:
	EnemyBullet();
	~EnemyBullet();

	virtual void Initialize() override;	// 初期化処理
	virtual void Update()override;		// 更新処理
	virtual void Draw() const override;	// 描画処理
	virtual void Finalize() override;	// 終了時処理

	// 当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_obhect)override;

private:
	void AnimeControl();	// アニメーション制御
	void Movement();		// 移動処理
};

