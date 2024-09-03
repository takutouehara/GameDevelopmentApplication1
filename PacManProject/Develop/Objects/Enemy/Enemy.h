#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// �G�l�~�[���
enum eEnemyState
{
	IDLE,
	MOVE,
	IZIKE,
	EYE,
};

/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy : public GameObject
{
private:
	std::vector<int> move_animation;		// �ړ��̃A�j���[�V�����摜
	std::vector<int> eyes_animation;		// ���S�̃A�j���[�V�����摜
	std::vector<int> izike_animation;		// ����̃A�j���[�V�����摜
	Vector2D old_location;					// �O���location
	Vector2D velocity;						// �ړ���
	eEnemyState enemy_state;				// �G�l�~�[���					// �a��H�ׂ���
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
	ePanelID old_panel;						// �O��p�l�����

	// �ړ��A�j���[�V�����̏���
	const int animation_num[4] = { 0, 1, 2, 1, };

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// �G�l�~�[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�G�l�~�[�̏��</returns>
	eEnemyState GetEnemyState() const;

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);
};
