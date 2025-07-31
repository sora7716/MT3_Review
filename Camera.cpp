#include "Camera.h"
#include "Rendering.h"

//初期化
void Camera::Initialize(float windowWidth, float windowHeight) {
	windowWidth_ = windowWidth;
	windowHeight_ = windowHeight;
}

//更新
void Camera::Update() {
	MakeViewProjectionMatrix();
}

//ビュー射影行列のゲッター
Matrix4x4 Camera::GetViewProjectionMatrix() const {
	return viewProjectionMatrix_;
}

//ビューポート行列のゲッター
Matrix4x4 Camera::GetViewportMatrix() const {
	return viewportMatrix_;
}

//トランスフォームデータのセッター
void Camera::SetTransformData(const TransformData& transformData) {
	transformData_ = transformData;
}

//ビュー射影行列の作成
void Camera::MakeViewProjectionMatrix() {
	worldMatrix_ = Rendering::GetInstance()->MakeAffineMatrix(transformData_);
	viewMatrix_ = worldMatrix_.Inverse();
	projectionMatrix_ = Rendering::GetInstance()->MakePerspectiveFovMatrix(0.45f, windowWidth_ / windowHeight_, 0.1f, 100.0f);
	viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_;
	viewportMatrix_ = Rendering::GetInstance()->MakeViewportMatrix(0, 0, windowWidth_, windowHeight_, 0.0f, 1.0f);
}
