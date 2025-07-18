#include "ScreenPrintf.h"
#include <Novice.h>
#include <cassert>

//インスタンスのゲッター
ScreenPrintf* ScreenPrintf::GetInstance() {
	assert(!isFinalize && "GetInstance() called after Finalize()");
	if (instance == nullptr) {
		instance = new ScreenPrintf();
	}
	return instance;
}

//ベクトルのスクリーンプリント
void ScreenPrintf::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

//終了
void ScreenPrintf::Finalize() {
	delete instance;
	instance = nullptr;
	isFinalize = true;
}