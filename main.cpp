#include <Novice.h>
#include <imgui.h>
#include <cstdint>
#include "ScreenPrintf.h"
#include "Rendering.h"
#include "Camera.h"
#include <numbers>
#include <cmath>

const char kWindowTitle[] = "GSManager";
const float kWindowWidth = 1280; // ウィンドウの幅
const float kWindowHeight = 720; // ウィンドウの高さ

//球データ
struct SphereData {
	Vector3 center;//中心
	float radius;//半径
};

/// <summary>
/// グリッドの描画
/// </summary>
/// <param name="viewProjectionMatrix">ビュー射影行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
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

		//色の設定
		uint32_t color = 0xAAAAAAFF;
		if (xIndex == kSubdivision / 2) {
			color = BLACK; // 中央の線は黒色にする
		}

		//描画
		Novice::DrawLine(
			static_cast<int32_t>(screenStartPos.x),
			static_cast<int32_t>(screenStartPos.y),
			static_cast<int32_t>(screenEndPos.x),
			static_cast<int32_t>(screenEndPos.y),
			color
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

		//色の設定
		uint32_t color = 0xAAAAAAFF;
		if (zIndex == kSubdivision / 2) {
			color = BLACK; // 中央の線は黒色にする
		}

		//描画
		Novice::DrawLine(
			static_cast<int32_t>(screenStartPos.x),
			static_cast<int32_t>(screenStartPos.y),
			static_cast<int32_t>(screenEndPos.x),
			static_cast<int32_t>(screenEndPos.y),
			color
		);
	}

}

/// <summary>
/// スフィアの描画
/// </summary>
/// <param name="viewProjection">ビュー射影行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
void DrawSphere(const SphereData& sphereData, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix) {
	const uint32_t kSubdivision = 10;//分割数
	const float kPi = std::numbers::pi_v<float>;//円周率
	const float kLonEvery = 2.0f * kPi / static_cast<float>(kSubdivision);//経度分割1つ分の長さ
	const float kLatEvery = kPi / static_cast<float>(kSubdivision);//緯度分割1つ分の長さ

	//緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++) {
		float lat = -kPi / 2.0f + kLatEvery * static_cast<float>(latIndex);

		//経度方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++) {
			float lon = static_cast<float>(lonIndex) * kLonEvery;

			// 球面座標からワールド座標に変換
			Vector3 a = {
				std::cos(lat) * std::cos(lon),
				std::sin(lat),
				std::cos(lat) * std::sin(lon)
			};

			Vector3 b = {
				std::cos(lat + kLatEvery) * std::cos(lon),
				std::sin(lat + kLatEvery),
				std::cos(lat + kLatEvery) * std::sin(lon)
			};

			Vector3 c = {
				std::cos(lat) * std::cos(lon + kLonEvery),
				std::sin(lat),
				std::cos(lat) * std::sin(lon + kLonEvery)
			};

			//球の半径と中心を考慮して座標を調整
			a = a * sphereData.radius + sphereData.center;
			b = b * sphereData.radius + sphereData.center;
			c = c * sphereData.radius + sphereData.center;

			//スクリーン座標に変換
			Vector3 screenA = Rendering::GetInstance()->Transform(a, viewProjection);
			screenA = Rendering::GetInstance()->Transform(screenA, viewportMatrix);

			Vector3 screenB = Rendering::GetInstance()->Transform(b, viewProjection);
			screenB = Rendering::GetInstance()->Transform(screenB, viewportMatrix);

			Vector3 screenC = Rendering::GetInstance()->Transform(c, viewProjection);
			screenC = Rendering::GetInstance()->Transform(screenC, viewportMatrix);

			// 経度線
			Novice::DrawLine(
				static_cast<int32_t>(screenA.x),
				static_cast<int32_t>(screenA.y),
				static_cast<int32_t>(screenB.x),
				static_cast<int32_t>(screenB.y),
				BLACK
			);

			// 緯度線
			Novice::DrawLine(
				static_cast<int32_t>(screenA.x),
				static_cast<int32_t>(screenA.y),
				static_cast<int32_t>(screenC.x),
				static_cast<int32_t>(screenC.y),
				BLACK
			);
		}
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
	TransformData cameraTransformData = { {1.0f,1.0f,1.0f},{0.26f,0.0f,0.0f},{0.0f,1.9f,-6.49f} };

	//球
	SphereData sphereData = { {}, 0.71f };
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
		DrawSphere(sphereData, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
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
