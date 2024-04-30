#include "WingEnemy.h"
#include "DxLib.h"

// �R���X�g���N�^
WingEnemy::WingEnemy() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

// �f�X�g���N�^
WingEnemy::~WingEnemy()
{
}

// ����������
void WingEnemy::Initialize()
{
	// �摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");

	// �G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�R�E�����̉摜������܂���B");
	}

	// �����̐ݒ�
	radian = 0.0;

	// �傫���̐ݒ�
	scale = 64.0;

	// �����摜�̐ݒ�
	image = animation[0];
}

// �X�V����
void WingEnemy::Update()
{
	AnimeControl();	// �A�j���[�V��������
}

// �`�揈��
void WingEnemy::Draw() const
{
	// �G�l�~�[�摜�̕`��
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);
}

// �I��������
void WingEnemy::Finalize()
{
	// �g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

// �����蔻��ʒm����
void WingEnemy::OnHitCollision(GameObject* hit_obhect)
{
	// �����������̏���
}

// �A�j���[�V�������䏈��
void WingEnemy::AnimeControl()
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
