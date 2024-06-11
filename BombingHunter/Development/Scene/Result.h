#pragma once

class Result
{
private:
	int image[3];			// 画像
	int number[10];			// Number画像
	int number_count_tp;	// Numberカウントtp
	int number_count_op;	// Numberカウントop
	int animation_count;	// アニメーション時間

public:
	Result();
	~Result();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();
	void Storage();

private:
	void TimerControl();
};

