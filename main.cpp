#include <Novice.h>
#include "ScreenPrintf.h"

const char kWindowTitle[] = "GSManager";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Matrix4x4 m1 = {
		3.2f,0.7f,9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f
	};

	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};

	Matrix4x4 add = {};
	Matrix4x4 multiply = {};
	Matrix4x4 sub = {};
	Matrix4x4 inverse1 = {};
	Matrix4x4 inverse2 = {};
	Matrix4x4  transpose1 = {};
	Matrix4x4  transpose2 = {};
	Matrix4x4  identity = {};

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
		add = m1 + m2;
		multiply = m1 * m2;
		sub = m1 - m2;
		inverse1 = ~m1;
		inverse2 = ~m2;
		transpose1 = m1.Transpose();
		transpose2 = m2.Transpose();
		identity = Matrix4x4::Indentity4x4();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, 0, add, "Add");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, ScreenPrintf::kRowHeight * 5, sub, "Subtract");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, ScreenPrintf::kRowHeight * 5 * 2, multiply, "Multiply");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, ScreenPrintf::kRowHeight * 5 * 3, inverse1, "inverse4");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, ScreenPrintf::kRowHeight * 5 * 4, inverse2, "inverse2");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(ScreenPrintf::kColumnWidth * 5, 0, transpose1, "transpose1");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(ScreenPrintf::kColumnWidth * 5, ScreenPrintf::kRowHeight * 5, transpose2, "transpose2");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(ScreenPrintf::kColumnWidth * 5, ScreenPrintf::kRowHeight * 5 * 2, identity, "identity");
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
