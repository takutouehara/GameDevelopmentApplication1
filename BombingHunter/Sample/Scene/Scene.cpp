#include "Scene.h"

#include "../Object/Player/Player.h"
#include "../Object/Enemy/BoxEnemy.h"
#include "../Object/Enemy/WingEnemy.h"
#include "../Object/Enemy/Harpy.h"
#include "../Object/Enemy/GoldEnemy.h"


// コンストラクタ
Scene::Scene():objects()
{
}

// デストラクタ
Scene::~Scene()
{
	// 忘れ防止
	Finalize();
}

// 初期化処理
void Scene::Initialize()
{
	// プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 90.0f));
	// BoxEnemyを生成する
	CreateObject<BoxEnemy>(Vector2D(560.0f, 360.0f));
	// WingEnemyを生成する
	//CreateObject<WingEnemy>(Vector2D(420.0f, 360.0f));
	// Harpyを生成する
	//CreateObject<Harpy>(Vector2D(280.0f, 360.0f));
	// GoldEnemyを生成する
	//CreateObject<GoldEnemy>(Vector2D(140.0f, 360.0f));
}

// 更新処理
void Scene::Update()
{
	// シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
}

// 描画処理
void Scene::Draw() const
{
	// シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

// 終了時処理
void Scene::Finalize()
{
	// 動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	// 各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	// 動的配列の解放
	objects.clear();
}
