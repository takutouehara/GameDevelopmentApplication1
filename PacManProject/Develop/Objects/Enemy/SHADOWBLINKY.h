#pragma once

#include "../Enemy/EnemyBase.h"

// エネミーの状態
enum eEnemyState
{
	IDOL,
	MOVE,
	IZIKE,
	EYE,
};

class SHADOWBLINKY : public EnemyBase
{
private:
	std::vector<int> move_animation;	// 移動のアニメーション画像
	std::vector<int> eyes_animation;	// 死亡のアニメーション画像
	Vector2D		 old_location;		// 前回のlocation
	Vector2D		 velocity;			// 移動量
	eEnemyState		 enemy_state;		// プレイヤー状態

public:
	SHADOWBLINKY();
	virtual ~SHADOWBLINKY();

	virtual void Initialize() override;									// 初期化処理
	virtual void Update(float delta_second) override;					// 更新処理
	virtual void Draw(const Vector2D& screen_offset) const override;	// 描画処理
	virtual void Finalize() override;									// 終了時処理
	
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

public:
	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>エネミーの状態</returns>
	eEnemyState GetEnamyState() const;

};

