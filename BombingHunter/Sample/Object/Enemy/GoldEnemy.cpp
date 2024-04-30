#include "GoldEnemy.h"
#include "DxLib.h"

// �R���X�g���N�^
GoldEnemy::GoldEnemy() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
}

// �f�X�g���N�^
GoldEnemy::~GoldEnemy()
{
}

// ����������
void GoldEnemy::Initialize()
{
	// �摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");

	// �G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�_�C���e�L�̉摜������܂���B");
	}

	// �����̐ݒ�
	radian = 0.0;

	// �傫���̐ݒ�
	scale = 64.0;

	// �����摜�̐ݒ�
	image = animation[0];
}

// �X�V����
void GoldEnemy::Update()
{
	AnimeControl();	// �A�j���[�V��������
}

// �`�揈��
void GoldEnemy::Draw() const
{
	// �G�l�~�[�摜�̕`��
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);
}

// �I��������
void GoldEnemy::Finalize()
{
	// �g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
}

// �����蔻��ʒm����
void GoldEnemy::OnHitCollision(GameObject* hit_obhect)
{
	// �����������̏���
}

// �A�j���[�V�������䏈��
void GoldEnemy::AnimeControl()
{
	// �t���[���J�E���g�����Z����
	animation_count++;

	// 60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		// �J�E���g�̃��Z�b�g
		animation_count = 0;

		/*
		// �摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
		*/
		if (image == animation[0])
		{
			for (int i = 0; i < 5; i++)
			{
				image = animation[i];
			}
		}
		else if (image == animation[4])
		{
			image = animation[0];
		}
		
	}
}
