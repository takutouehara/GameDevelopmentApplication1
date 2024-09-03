#include "Enemy.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "../Food/Food.h"

#define D_PLAYER_SPEED	(50.0f)

Enemy::Enemy() :
	move_animation(),
	izike_animation(),
	eyes_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::MOVE),
	animation_time(0.0f),
	animation_count(0),
	old_panel(ePanelID::NONE)
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyes_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
	izike_animation = rm->GetImages("Resource/Images/.png", 12, 12, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;
}

void Enemy::Update(float delta_second)
{
	// �v���C���[��Ԃɂ���āA�����ς���
	switch (enemy_state)
	{
	case eEnemyState::IDLE:
		// �摜�̐ݒ�
		image = move_animation[9];
		break;
	case eEnemyState::MOVE:
		// �ړ�����
		Movement(delta_second);
		// �A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::EYE:
		// �P�ޒ��̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			// ����������
			if (animation_count >= eyes_animation.size())
			{
				enemy_state = eEnemyState::IDLE;
				animation_count = 0;
			}
		}
		image = eyes_animation[animation_count];
		break;
	case eEnemyState::IZIKE:

		break;
	default:
		break;
	}
}

void Enemy::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void Enemy::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eyes_animation.clear();
	izike_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Enemy::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Enemy����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}

	// ���������I�u�W�F�N�g���G��������
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::EYE;
	}
}

/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
eEnemyState Enemy::GetEnemyState() const
{
	return enemy_state;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Enemy::Movement(float delta_second)
{
	// ���͏�Ԃ̎擾
	InputManager* input = InputManager::GetInstance();

	// ���݃p�l���̏�Ԃ��m�F
	ePanelID panel = StageData::GetPanelData(location);

	// �O����W�̍X�V
	old_location = location;

	// �O��p�l���̍X�V
	old_panel = panel;

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += velocity * D_PLAYER_SPEED * delta_second;

	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
	if (location.x < 0.0f)
	{
		old_location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		old_location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Enemy::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
	}
}
