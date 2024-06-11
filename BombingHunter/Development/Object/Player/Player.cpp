#include "Player.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

// �ÓI�����o�ϐ��錾
float Player::player_x = 320.0f;
float Player::player_y = 150.0f;

// �R���X�g���N�^
Player::Player() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

// �f�X�g���N�^
Player::~Player()
{
}

// ����������
void Player::Initialize()
{
	// �摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Tri-pilot/1.png");
	animation[1] = LoadGraph("Resource/Images/Tri-pilot/2.png");

	// �G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�g���p�C���b�g�̉摜������܂���B");
	}

	// �����̐ݒ�
	radian = 0.0;

	// �傫���̐ݒ�
	box_size = 64.0;

	// �����摜�̐ݒ�
	image = animation[0];
}

// �X�V����
void Player::Update()
{
	// �ړ�����
	Movement();
	// �A�j���[�V��������
	AnimeControl();

}

// �`�揈��
void Player::Draw() const
{
	// �v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, filp_flag);

	// �f�o�b�O�p
#if _DEBUG
	// �����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);
#endif

}

// �I��������
void Player::Finalize()
{
	// �g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

// �����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_obhect)
{
	// �����������̏���
}

// �ړ�����
void Player::Movement()
{
	// �ړ��̑���
	Vector2D veloctiy = 0.0f;

	// ���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		veloctiy.x += -1.0f;
		filp_flag = TRUE;
		player_x += veloctiy.x;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		veloctiy.x += 1.0f;
		filp_flag = FALSE;
		player_x += veloctiy.x;
	}
	else
	{
		veloctiy.x += 0.0f;
	}

	// ���݂̈ʒu���W�ɑ��������Z����
	location += veloctiy;
}

// �A�j���[�V��������
void Player::AnimeControl()
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
