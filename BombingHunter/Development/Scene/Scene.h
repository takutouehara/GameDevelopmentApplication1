#pragma once

#include <vector>
#include "../Object/GameObject.h"

class Scene:public GameObject
{
private:
	std::vector<GameObject*> objects;
	int background;			// 背景
	int FreamCount;			// フレームカウント

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();

	static int BulletCount;	// 弾の出現数
	static int EnemyCount;	// 敵の出現数
	//std::vector<GameObject*> objects;


private:
	// 当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	// オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		// 指定したクラスを生成する
		T* new_instance = new T();
		// GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		// エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("ゲームオブジェクトが生成できませんでした\n");
		}

		// 初期化処理
		new_object->Initialize();

		// 位置情報の設定
		new_object->SetLocation(location);

		// オブジェクトリストに追加
		objects.push_back(new_object);

		// オブジェクトのポインタを返却
		return new_instance;
	}
};

