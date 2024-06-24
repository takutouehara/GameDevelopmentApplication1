#pragma once

#include "../GameObject.h"

class PlayerBullet :public GameObject
{
private:
	int animation[4];		// �A�j���[�V�����摜
	int animation_count;	// �A�j���[�V��������
	Vector2D direction;		// ����
	
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void Initialize() override;	// ����������
	virtual void Update()override;		// �X�V����
	virtual void Draw() const override;	// �`�揈��
	virtual void Finalize() override;	// �I��������

	// �����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object)override;

private:
	void AnimeControl();	// �A�j���[�V��������
	void Movement();		// �ړ�����
};

