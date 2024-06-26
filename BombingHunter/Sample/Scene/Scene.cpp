#include "Scene.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/BoxEnemy.h"
#include "../Object/Enemy/WingEnemy.h"
#include "../Object/Enemy/Harpy.h"
#include "../Object/Enemy/GoldEnemy.h"

#define D_PIVOT_CENTER

// コンストラクタ
Scene::Scene() :objects()
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
	//CreateObject<BoxEnemy>(Vector2D(560.0f, 360.0f));
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

	// オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			// 当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	// Zキーを押したら敵を生成する
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
// 当たり判定チェック処理(単系の中心で当たり判定をとる)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	// ２つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();
	// ２つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;
	// 距離より大きさが大きい場合HITとする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		// 当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else
// 当たり判定チェック処理(左上頂点の座標から当たり判定計算を行う)
void Scene::HitCheckobject(GameObject* a, GameObject* b)
{
	// 右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();
	// 短形Aと短形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) && (a->GetLocation().y < b_lower_right.y) && (a_lower_right.x > b->GetLocation().x) && (a_lower_right.y > b->GetLocation().y))
	{
		// オブジェクトに対してHIT判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER
