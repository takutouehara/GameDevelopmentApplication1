#pragma once

#include "../Enemy/EnemyBase.h"

// �G�l�~�[�̏��
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
	std::vector<int> move_animation;	// �ړ��̃A�j���[�V�����摜
	std::vector<int> eyes_animation;	// ���S�̃A�j���[�V�����摜
	Vector2D		 old_location;		// �O���location
	Vector2D		 velocity;			// �ړ���
	eEnemyState		 enemy_state;		// �v���C���[���

public:
	SHADOWBLINKY();
	virtual ~SHADOWBLINKY();

	virtual void Initialize() override;									// ����������
	virtual void Update(float delta_second) override;					// �X�V����
	virtual void Draw(const Vector2D& screen_offset) const override;	// �`�揈��
	virtual void Finalize() override;									// �I��������
	
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

public:
	/// <summary>
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�G�l�~�[�̏��</returns>
	eEnemyState GetEnamyState() const;

};

