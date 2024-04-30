#include "Scene.h"

#include "../Object/Player/Player.h"
#include "../Object/Enemy/BoxEnemy.h"
#include "../Object/Enemy/WingEnemy.h"
#include "../Object/Enemy/Harpy.h"
#include "../Object/Enemy/GoldEnemy.h"


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
	CreateObject<Player>(Vector2D(320.0f, 90.0f));
	// BoxEnemy�𐶐�����
	CreateObject<BoxEnemy>(Vector2D(560.0f, 360.0f));
	// WingEnemy�𐶐�����
	//CreateObject<WingEnemy>(Vector2D(420.0f, 360.0f));
	// Harpy�𐶐�����
	//CreateObject<Harpy>(Vector2D(280.0f, 360.0f));
	// GoldEnemy�𐶐�����
	//CreateObject<GoldEnemy>(Vector2D(140.0f, 360.0f));
}

// �X�V����
void Scene::Update()
{
	// �V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
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
