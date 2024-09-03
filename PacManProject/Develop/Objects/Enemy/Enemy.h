#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// エネミー状態
enum eEnemyState
{
	IDLE,
	MOVE,
	IZIKE,
	EYE,
};

/// <summary>
/// エネミークラス
/// </summary>
class Enemy : public GameObject
{
private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> eyes_animation;		// 死亡のアニメーション画像
	std::vector<int> izike_animation;		// 特殊のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// エネミー状態					// 餌を食べた数
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	ePanelID old_panel;						// 前回パネル情報

	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1, };

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// エネミーの状態を取得する
	/// </summary>
	/// <returns>エネミーの状態</returns>
	eEnemyState GetEnemyState() const;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);
};
