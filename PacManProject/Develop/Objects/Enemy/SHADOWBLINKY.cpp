#include "SHADOWBLINKY.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "EnemyBase.h"
#include "DxLib.h"

SHADOWBLINKY::SHADOWBLINKY() :
	move_animation(),
	eyes_animation(),
	enemy_state(eEnemyState::IDOL),
	old_location(),
	velocity(0.0f)
{

}

SHADOWBLINKY::~SHADOWBLINKY()
{

}

void SHADOWBLINKY::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation =  rm->GetImages("Resource/Images/monster.png", 12, 12, 1, 32, 32);
	eyes_animation = rm->GetImages("Resource/Images/eyes.png", 11, 11, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

}

void SHADOWBLINKY::Update(float delta_second)
{
	EnemyBase* enemy_base = new EnemyBase;

	// �v���C���[��Ԃɂ���āA�����ς���
	switch (enemy_state)
	{
	case eEnemyState::IDOL:
		// �摜�̐ݒ�
		image = move_animation[9];
		break;
	case eEnemyState::MOVE:
		// �ړ�����
		Movement(delta_second);
		// �A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::IZIKE:
		break;
	case eEnemyState::EYE:
		break;
	default:
		break;
	}
}

void SHADOWBLINKY::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void SHADOWBLINKY::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eyes_animation.clear();
}

void SHADOWBLINKY::Movement(float delta_second)
{

}

void SHADOWBLINKY::AnimationControl(float delta_second)
{

}

eEnemyState SHADOWBLINKY::GetEnamyState() const
{
	return eEnemyState();
}
