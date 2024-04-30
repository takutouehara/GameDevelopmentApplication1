#include "Scene.h"
#include "../Object/"
#include "../Object/Player/Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#define D_PIVOT_CENTER

// �R���X�g���N�^
Scene::Scene():objects()
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
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
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

	// Z�L�[����������A�G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<BoxEnemy>(Vector2D(100.0f, 400.0f));
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

void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	// �Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	// �Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	// �������傫�����傫���ꍇ�AHIT�Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		// �����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else

#endif // D_PIVOT_CENTER
