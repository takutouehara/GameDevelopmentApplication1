#include "Scene.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/BoxEnemy.h"
#include "../Object/Enemy/WingEnemy.h"
#include "../Object/Enemy/Harpy.h"
#include "../Object/Enemy/GoldEnemy.h"
#include "../Object/Enemy/EnemyBullet.h"
#include "../Object/Player/PlayerBullet.h"

#define D_PIVOT_CENTER

// �R���X�g���N�^
Scene::Scene() :objects()
{
}

// �f�X�g���N�^
Scene::~Scene()
{
	// �Y��h�~
	Finalize();
}

// ����������
void Scene::Initialize()
{
	// �v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 90.0f));
}

// �X�V����
void Scene::Update()
{
	// �V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	// �I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			// �����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	// Z�L�[����������G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<BoxEnemy>(Vector2D(100.0f, 400.0f));
	}
	// X�L�[����������G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_X))
	{
		CreateObject<WingEnemy>(Vector2D(200.0f, 400.0f));
	}
	// C�L�[����������G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<Harpy>(Vector2D(300.0f, 400.0f));
	}
	// V�L�[����������G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_V))
	{
		CreateObject<GoldEnemy>(Vector2D(400.0f, 400.0f));
	}
	// B�L�[����������G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<EnemyBullet>(Vector2D(500.0f, 400.0f));
	}
	// E�L�[����������G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_E))
	{
		CreateObject<PlayerBullet>(Vector2D(400.0f, 90.0f));
	}
}

// �`�揈��
void Scene::Draw() const
{
	// �V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

// �I��������
void Scene::Finalize()
{
	// ���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	// �e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	// ���I�z��̉��
	objects.clear();
}

#ifdef D_PIVOT_CENTER
// �����蔻��`�F�b�N����(�P�n�̒��S�œ����蔻����Ƃ�)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	// �Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();
	// �Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;
	// �������傫�����傫���ꍇHIT�Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		// �����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else
// �����蔻��`�F�b�N����(���㒸�_�̍��W���瓖���蔻��v�Z���s��)
void Scene::HitCheckobject(GameObject* a, GameObject* b)
{
	// �E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();
	// �Z�`A�ƒZ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) && (a->GetLocation().y < b_lower_right.y) && (a_lower_right.x > b->GetLocation().x) && (a_lower_right.y > b->GetLocation().y)) 
	{
		// �I�u�W�F�N�g�ɑ΂���HIT�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER
