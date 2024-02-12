#include "Barrier.h"
#include"DxLib.h"

Barrier::Barrier():image(NULL),life_span(1000)
{
	// 画像読込
	image = LoadGraph("Resource/images/barrier.png");

	// エラーチェック
	if (image == -1) {
		throw("バリアの画像がありません");
	}
}

Barrier::~Barrier()
{
	// 画像消去
	DeleteGraph(image);
}

void Barrier::Draw(const Vector2D& location)
{
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

bool Barrier::IsFinished(float speed)
{
	life_span -= speed;		// フレームごとにlife_spanをマイナス
	return (life_span<=0);	// ライフが0以下かどうかを返す
}
