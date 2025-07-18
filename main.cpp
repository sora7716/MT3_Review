#include <Novice.h>
#include "ScreenPrintf.h"

const char kWindowTitle[] = "GSManager";

const int kRowHeight = 20;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1 = { 1.0f,3.0f,-5.0f };
	Vector3 v2 = { 4.0f,-1.0f,2.0f };
	float k = 4.0f;

	Vector3 add = {};
	Vector3 sub = {};
	Vector3 multiply = {};
	float dot = 0.0f;
	float length = 0.0f;
	Vector3 normalize = {};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		add = v1 + v2;
		sub = v1 - v2;
		multiply = v1 * k;
		dot = v1.Dot(v2);
		length = v1.Length();
		normalize = v2.Normalize();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ScreenPrintf::GetInstance()->VectorScreenPrintf(0, 0, add, " : Add");
		ScreenPrintf::GetInstance()->VectorScreenPrintf(0, kRowHeight, sub, " : Subtract");
		ScreenPrintf::GetInstance()->VectorScreenPrintf(0, kRowHeight*2, multiply, " : Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", dot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", length);
		ScreenPrintf::GetInstance()->VectorScreenPrintf(0, kRowHeight * 5, normalize, " : Normalize");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	//スクリーンプリントの終了
	ScreenPrintf::GetInstance()->Finalize();
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
