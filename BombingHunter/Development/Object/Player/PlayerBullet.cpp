#include "PlayerBullet.h"
#include "DxLib.h"

// �R���X�g���N�^
PlayerBullet::PlayerBullet() : animation_count(0.0f), direction(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

// �f�X�g���N�^
PlayerBullet::~PlayerBullet()
{
}

// ����������
void PlayerBullet::Initialize()
{
	// �摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");

	// �G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("�v���C���[�o���b�g�̉摜������܂���B");
	}

	// �����̐ݒ�
	radian = 0.0;

	// �傫���̐ݒ�
	box_size = 50.0;

	// �����摜�̐ݒ�
	image = animation[0];

	// �����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.5f);
}

// �X�V����
void PlayerBullet::Update()
{
	// �ړ�����
	Movement();

	// �A�j���[�V��������
	AnimeControl();
}

// �`�揈��
void PlayerBullet::Draw() const
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
void PlayerBullet::Finalize()
{
	// �g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

// �����蔻��ʒm����
void PlayerBullet::OnHitCollision(GameObject* hit_obhect)
{
	// �����������̏���
	direction = 0.0f;
}

// �ړ�����
void PlayerBullet::Movement()
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
void PlayerBullet::AnimeControl()
{
	// �t���[���J�E���g�����Z����
	animation_count++;

	// 30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		// �J�E���g�̃��Z�b�g
		animation_count = 0;
	}
}