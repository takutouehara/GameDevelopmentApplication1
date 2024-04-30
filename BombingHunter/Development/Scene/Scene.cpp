#include "Scene.h"
#include "../Object/"
#include "../Object/Player/Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#define D_PIVOT_CENTER

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
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

// 更新処理
void Scene::Update()
{
	// シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	// オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			// 当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	// Zキーを押したら、敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<BoxEnemy>(Vector2D(100.0f, 400.0f));
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

#ifdef D_PIVOT_CENTER

void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	// ２つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	// ２つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	// 距離より大きさが大きい場合、HITとする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		// 当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else

#endif // D_PIVOT_CENTER
