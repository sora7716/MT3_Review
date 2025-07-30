#include "Rendering.h"
#include "Math.h"
#include <cmath>
#include <cassert>

//インスタンスのゲッター
Rendering* Rendering::GetInstance() {
	assert(!isFinalize && "GetInstance() called after Finalize()");
	if (instance == nullptr) {
		instance = new Rendering();
	}
	return instance;
}

//拡縮行列の作成
Matrix4x4 Rendering::MakeScaleMatrix(const Vector3& scale) {
	//単位行列で初期化
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	return result;
}

//X軸の回転行列の作成
Matrix4x4 Rendering::MakeRotateXMatrix(float theta) {
	//単位行列で初期化
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result.m[1][1] = std::cos(theta);
	result.m[1][2] = std::sin(theta);
	result.m[2][1] = -std::sin(theta);
	result.m[2][2] = std::cos(theta);
	return result;
}

//Y軸の回転行列の作成
Matrix4x4 Rendering::MakeRotateYMatrix(float theta) {
	//単位行列で初期化
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result.m[0][0] = std::cos(theta);
	result.m[0][2] = -std::sin(theta);
	result.m[2][0] = std::sin(theta);
	result.m[2][2] = std::cos(theta);
	return result;
}

//Z軸の回転行列の作成
Matrix4x4 Rendering::MakeRotateZMatrix(float theta) {
	//単位行列で初期化
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result.m[0][0] = std::cos(theta);
	result.m[0][1] = std::sin(theta);
	result.m[1][0] = -std::sin(theta);
	result.m[1][1] = std::cos(theta);
	return result;
}

//回転行列の作成
Matrix4x4 Rendering::MakeRotateMatrix(const Vector3& rotate) {
	return MakeRotateXMatrix(rotate.x) * MakeRotateYMatrix(rotate.y) * MakeRotateZMatrix(rotate.z);
}

//平行移動行列の作成
Matrix4x4 Rendering::MakeTranslateMatrix(const Vector3& translate) {
	//単位行列で初期化
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}

//アフィン行列の作成
Matrix4x4 Rendering::MakeAffineMatrix(const TransformData& transformData) {
	return MakeScaleMatrix(transformData.scale) * MakeRotateMatrix(transformData.rotate) * MakeTranslateMatrix(transformData.translate);
}

//正射影行列の作成
Matrix4x4 Rendering::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip){
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result = {
		2.0f / (right - left),0.0f,0.0f,0.0f,
		0.0f,2.0f / (top - bottom),0.0f,0.0f,
		0.0f,0.0f,1.0f / (farClip - nearClip),0.0f,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1.0f
	};
	return result;
}

//透視投影行列の作成
Matrix4x4 Rendering::MakePerspectiveFovMatrix(float fovY, float aspectRation, float nearClip, float farClip){
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result = {
		1.0f / aspectRation * Math::Cotangent(fovY / 2.0f),0.0f,0.0f,0.0f,
		0.0f,Math::Cotangent(fovY / 2.0f),0.0f,0.0f,
		0.0f,0.0f,farClip / (farClip - nearClip),1.0f,
		0.0f,0.0f,-(nearClip * farClip) / (farClip - nearClip),0.0f
	};
	return result;
}

//ビューポート行列の作成
Matrix4x4 Rendering::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth){
	Matrix4x4 result = Matrix4x4::Indentity4x4();
	result = {
		width / 2.0f,0.0f,0.0f,0.0f,
		0.0f,-height / 2.0f,0.0f,0.0f,
		0.0f,0.0f,maxDepth - minDepth,0.0f,
		left + width / 2.0f,top + height / 2.0f,minDepth,1.0f
	};
	return result;
}

//座標変換
Vector3 Rendering::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//終了
void Rendering::Finalize() {
	delete instance;
	instance = nullptr;
	isFinalize = true;
}
