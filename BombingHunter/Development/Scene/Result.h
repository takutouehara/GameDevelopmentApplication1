#pragma once

class Result
{
private:
	int image[3];			// �摜
	int number[10];			// Number�摜
	int number_count_tp;	// Number�J�E���gtp
	int number_count_op;	// Number�J�E���gop
	int animation_count;	// �A�j���[�V��������

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

