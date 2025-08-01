#include <Novice.h>
#include <imgui.h>
#include <cstdint>
#include "ScreenPrintf.h"
#include "Rendering.h"
#include "Camera.h"

const char kWindowTitle[] = "GSManager";
const float kWindowWidth = 1280; // ウィンドウの幅
const float kWindowHeight = 720; // ウィンドウの高さ

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//ベクトル
	Vector3 v1 = { 1.2f,-3.9f,2.5f };
	Vector3 v2 = { 2.8f,0.4f,-1.3f };
	Vector3 cross = v1.Cross(v2);

	//三角形
	Vector3 rotate = {};
	Vector3 translate = {};
	Matrix4x4 worldMatrix = Matrix4x4::Indentity4x4();
	Matrix4x4 worldViewProjectMatrix = Matrix4x4::Indentity4x4();
	Vector3 localVertices[3] = {
		{-1.0f,-1.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{1.0f,-1.0f,0.0f},
	};
	Vector3 screenVertices[3] = {};

	//カメラ
	Camera* camera = new Camera();
	camera->Initialize(kWindowWidth, kWindowHeight);
	Vector3 cameraPosition = { 0.0f, 0.0f, -10.0f };

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
		camera->SetTransformData({ {1.0f,1.0f,1.0f},{},cameraPosition });
		//カメラの更新
		camera->Update();
		//ワールド行列の作成
		worldMatrix = Rendering::GetInstance()->MakeAffineMatrix({ { 1.0f,1.0f,1.0f },rotate, translate });
		//ワールドビュー射影行列の計算
		worldViewProjectMatrix = worldMatrix * camera->GetViewProjectionMatrix();
		//座標変換
		for (uint32_t i = 0; i < 3; i++) {
			Vector3 ndcVertex = Rendering::GetInstance()->Transform(localVertices[i], worldViewProjectMatrix);
			screenVertices[i] = Rendering::GetInstance()->Transform(ndcVertex, camera->GetViewportMatrix());
		}

		ImGui::DragFloat3("rotate", &rotate.x, 0.1f);
		ImGui::DragFloat3("translate", &translate.x, 0.1f);
		ImGui::DragFloat3("cameraPosition", &cameraPosition.x, 0.1f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//文字の描画
		ScreenPrintf::GetInstance()->VectorScreenPrintf(0, 0, cross, "cross");

		//三角形の描画
		Novice::DrawTriangle(
			static_cast<int32_t>(screenVertices[0].x), static_cast<int32_t>(screenVertices[0].y),
			static_cast<int32_t>(screenVertices[1].x), static_cast<int32_t>(screenVertices[1].y),
			static_cast<int32_t>(screenVertices[2].x), static_cast<int32_t>(screenVertices[2].y),
			WHITE, kFillModeSolid
		);
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
