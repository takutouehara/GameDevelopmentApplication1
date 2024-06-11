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

// 静的メンバ変数宣言
int Scene::EnemyCount = 0;
int Scene::BulletCount = 0;
// ローカル変数宣言
Result* result = new Result();

// コンストラクタ
Scene::Scene() :objects(),background(NULL)
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
	CreateObject<Player>(Vector2D(Player::player_x, Player::player_y));

	// UIを表示する
	result->Initialize();

	// 背景画像の読み込み
	background = LoadGraph("Resource/Images/BackGround.png");
	// エラーチェック
	if (background == -1)
	{
		throw("背景の画像がありません。");
	}
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

	// UIを更新する
	result->Update();

	/*
	// Bキーを押したらエネミーバレットを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<EnemyBullet>(Vector2D(750.0f, 600.0f));
	}
	*/

	// SPACEキーを押したらプレイヤーバレットを生成する
	if (BulletCount < 5)
	{
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			CreateObject<PlayerBullet>(Vector2D(Player::player_x + 0.0f, Player::player_y + 70.0f));
			BulletCount++;
		}
	}
	//敵に当たったら減らす
	//BulletCount--;
	
	// 敵を生成する
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
	// 敵を倒したときに数を減らす
	//EnemyCount--;
}

// 描画処理
void Scene::Draw() const
{
	// 背景の生成
	DrawGraph(0, 0, background, TRUE);

	// シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	// UIを描画する
	result->Draw();
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

	// UIを終了する
	result->Finalize();
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
