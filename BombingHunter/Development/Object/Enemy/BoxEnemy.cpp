#include "BoxEnemy.h"
#include "DxLib.h"

// �R���X�g���N�^
BoxEnemy::BoxEnemy() :animation_count(0), direction(0.0f)
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
	box_size = 64.0;

	// �����摜�̐ݒ�
	image = animation[0];

	// �����i�s�����̐ݒ�
	direction = Vector2D(1.0f, -0.5f);
}

// �X�V����
void BoxEnemy::Update()
{
	// �ړ�����
	Movement();

	// �A�j���[�V��������
	AnimeControl();
}

// �`�揈��
void BoxEnemy::Draw() const
{
	// �摜���]
	int flip_flag = FALSE;

	// �i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	// �G�l�~�[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
	
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
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
	direction = 0.0f;
}

// �ړ�����
void BoxEnemy::Movement()
{
	// ��ʒ[�ɓ��B������i�s�����𔽓]����
	if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
	// �i�s�����Ɍ������Ĉʒu���W��ύX����
	location += direction;
}

// �A�j���[�V�������䏈��
void BoxEnemy::AnimeControl()
{
	// �t���[���J�E���g�����Z����
	animation_count++;

	// 30�t���[���ڂɓ��B������
	if (animation_count >= 30)
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