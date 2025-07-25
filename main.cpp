#include <Novice.h>
#include "ScreenPrintf.h"
#include "Rendering.h"

const char kWindowTitle[] = "GSManager";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 rotate = { 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMatrix = Rendering::GetInstance()->MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = Rendering::GetInstance()->MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = Rendering::GetInstance()->MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Rendering::GetInstance()->MakeRotateMatrix(rotate);

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, ScreenPrintf::kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, ScreenPrintf::kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		ScreenPrintf::GetInstance()->MatrixScreenPrintf(0, ScreenPrintf::kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");
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
	//レンダリングの終了
	Rendering::GetInstance()->Finalize();
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
