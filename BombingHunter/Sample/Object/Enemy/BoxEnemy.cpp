#include "BoxEnemy.h"
#include "../../Utility/Vector2D.h"
#include "DxLib.h"

// �R���X�g���N�^
BoxEnemy::BoxEnemy() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

// �f�X�g���N�^
BoxEnemy::~BoxEnemy()
{
}

// ����������
void BoxEnemy::Initialize()
{
	// �摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	// �G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�e�L�̉摜������܂���B");
	}

	// �����̐ݒ�
	radian = 0.0;

	// �傫���̐ݒ�
	scale = 64.0;

	// �����摜�̐ݒ�
	image = animation[0];

	// �ړ�����
	Movement();
}

// �X�V����
void BoxEnemy::Update()
{
	// �A�j���[�V��������
	AnimeControl();
}

// �`�揈��
void BoxEnemy::Draw() const
{
	// �G�l�~�[�摜�̕`��
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);
}

// �I��������
void BoxEnemy::Finalize()
{
	// �g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

// �����蔻��ʒm����
void BoxEnemy::OnHitCollision(GameObject* hit_obhect)
{
	// �����������̏���
}

// �A�j���[�V�������䏈��
void BoxEnemy::AnimeControl()
{
	// �t���[���J�E���g�����Z����
	animation_count++;

	// 60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		// �J�E���g�̃��Z�b�g
		animation_count = 0;

		// �摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}

// �ړ�����
void BoxEnemy::Movement()
{
	if (location.x >= 640.0f)
	{
		location.x += -10.0f;
	}
	else if (location.x <= 0.0f)
	{
		location.x += 1.0f;
	}
}