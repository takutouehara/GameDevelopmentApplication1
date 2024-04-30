#pragma once

#include "../GameObject.h"

class GoldEnemy :public GameObject
{
private:
	int animation[5];		// アニメーション画像
	int animation_count;	// アニメーション時間
	int filp_flag;			// 反転プラグ

public:
	GoldEnemy();
	~GoldEnemy();

	virtual void Initialize() override;	// 初期化処理
	virtual void Update()override;		// 更新処理
	virtual void Draw() const override;	// 描画処理
	virtual void Finalize() override;	// 終了時処理

	// 当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_obhect)override;

private:
	void AnimeControl();	// アニメーション制御
};

