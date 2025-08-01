#include <Novice.h>
#include <imgui.h>
#include <cstdint>
#include "ScreenPrintf.h"
#include "Rendering.h"
#include "Camera.h"

const char kWindowTitle[] = "GSManager";
const float kWindowWidth = 1280; // ウィンドウの幅
const float kWindowHeight = 720; // ウィンドウの高さ

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;//グリッドの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivision);//1つ分の長さ

	//奥から手前ヘの線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
		//ローカル座標を求める
		float z = -kGridHalfWidth + kGridEvery * static_cast<float>(xIndex);
		Vector3 localStartPos = { -kGridHalfWidth, 0.0f, z };
		Vector3 localEndPos = { kGridHalfWidth, 0.0f, z };

		//スクリーン座標に変換
		Vector3 screenStartPos = Rendering::GetInstance()->Transform(localStartPos, viewProjectionMatrix);
		screenStartPos = Rendering::GetInstance()->Transform(screenStartPos, viewportMatrix);
		Vector3 screenEndPos = Rendering::GetInstance()->Transform(localEndPos, viewProjectionMatrix);
		screenEndPos = Rendering::GetInstance()->Transform(screenEndPos, viewportMatrix);

		//描画
		Novice::DrawLine(
			static_cast<int32_t>(screenStartPos.x),
			static_cast<int32_t>(screenStartPos.y),
			static_cast<int32_t>(screenEndPos.x),
			static_cast<int32_t>(screenEndPos.y),
			0xAAAAAAFF
		);
	}


	//左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++) {
		//ローカル座標を求める
		float x = -kGridHalfWidth + kGridEvery * static_cast<float>(zIndex);
		Vector3 localStartPos = { x, 0.0f, -kGridHalfWidth };
		Vector3 localEndPos = { x, 0.0f, kGridHalfWidth };

		//スクリーン座標に変換
		Vector3 screenStartPos = Rendering::GetInstance()->Transform(localStartPos, viewProjectionMatrix);
		screenStartPos = Rendering::GetInstance()->Transform(screenStartPos, viewportMatrix);
		Vector3 screenEndPos = Rendering::GetInstance()->Transform(localEndPos, viewProjectionMatrix);
		screenEndPos = Rendering::GetInstance()->Transform(screenEndPos, viewportMatrix);

		//描画
		Novice::DrawLine(
			static_cast<int32_t>(screenStartPos.x),
			static_cast<int32_t>(screenStartPos.y),
			static_cast<int32_t>(screenEndPos.x),
			static_cast<int32_t>(screenEndPos.y),
			0xAAAAAAFF
		);
	}

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//カメラ
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);
	TransformData cameraTransformData = { {1.0f,1.0f,1.0f},{},{0.0f,0.0f,-10.0f} };

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
		//カメラのトランスフォームデータを設定
		camera->SetTransformData(cameraTransformData);
		//カメラの更新
		camera->Update();
		///
		/// ↑更新処理ここまで
		///
		ImGui::Begin("camera");
		ImGui::DragFloat3("rotate", &cameraTransformData.rotate.x, 0.1f);
		ImGui::DragFloat3("translate", &cameraTransformData.translate.x, 0.1f);
		ImGui::End();
		///
		/// ↓描画処理ここから
		///
		DrawGrid(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
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
	//カメラの解放
	delete camera;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
