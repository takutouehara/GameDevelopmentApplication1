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
#include "Result.h"

#define D_PIVOT_CENTER

// �ÓI�����o�ϐ��錾
int Scene::EnemyCount = 0;
int Scene::BulletCount = 0;
// ���[�J���ϐ��錾
Result* result = new Result();

// �R���X�g���N�^
Scene::Scene() :objects(),background(NULL)
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
	CreateObject<Player>(Vector2D(Player::player_x, Player::player_y));

	// UI��\������
	result->Initialize();

	// �w�i�摜�̓ǂݍ���
	background = LoadGraph("Resource/Images/BackGround.png");
	// �G���[�`�F�b�N
	if (background == -1)
	{
		throw("�w�i�̉摜������܂���B");
	}
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

	// UI���X�V����
	result->Update();

	/*
	// B�L�[����������G�l�~�[�o���b�g�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<EnemyBullet>(Vector2D(750.0f, 600.0f));
	}
	*/

	// SPACE�L�[����������v���C���[�o���b�g�𐶐�����
	if (BulletCount < 5)
	{
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			CreateObject<PlayerBullet>(Vector2D(Player::player_x + 0.0f, Player::player_y + 70.0f));
			BulletCount++;
		}
	}
	//�G�ɓ��������猸�炷
	//BulletCount--;
	
	// �G�𐶐�����
	if (EnemyCount < 10)
	{
		if ((GetRand(100000) % 100) && (GetRand(100000) % 100) == 0)
		//if (GetRand(9) == 5)
		{
			switch (GetRand(3))
			{
			case 0:
				CreateObject<BoxEnemy>(Vector2D(100.0f, 550.0f));
				EnemyCount++;
				break;
			case 1:
				CreateObject<WingEnemy>(Vector2D(100.0f, 480.0f));
				EnemyCount++;
				break;
			case 2:
				CreateObject<Harpy>(Vector2D(100.0f, 410.0f));
				EnemyCount++;
				break;
			case 3:
				CreateObject<GoldEnemy>(Vector2D(100.0f, 620.0f));
				EnemyCount++;
				break;
			default:
				break;
			}
		}
	}
	// �G��|�����Ƃ��ɐ������炷
	//EnemyCount--;
}

// �`�揈��
void Scene::Draw() const
{
	// �w�i�̐���
	DrawGraph(0, 0, background, TRUE);

	// �V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	// UI��`�悷��
	result->Draw();
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

	// UI���I������
	result->Finalize();
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
