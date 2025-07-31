#pragma once
#include "RenderingData.h"
#include "Matrix4x4.h"

/// <summary>
/// カメラ
/// </summary>
class Camera {
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Camera() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Camera() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="windowWidth">画面の幅</param>
	/// <param name="windowHeight">画面の高さ</param>
	void Initialize(float windowWidth,float windowHeight);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ビュー射影行列のゲッター
	/// </summary>
	/// <returns>ビュー射影行列</returns>
	Matrix4x4 GetViewProjectionMatrix() const;

	/// <summary>
	/// ビューポート行列のゲッター
	/// </summary>
	/// <returns>ビューポート行列</returns>
	Matrix4x4 GetViewportMatrix() const;

	/// <summary>
	/// トランスフォームデータのセッター
	/// </summary>
	/// <param name="transformData">トランスフォームデータ</param>
	void SetTransformData(const TransformData& transformData);
private://メンバ関数
	/// <summary>
	/// ビュー射影行列を作成
	/// </summary>
	void MakeViewProjectionMatrix();
private://メンバ変数
	float windowWidth_ = 0.0f; //画面の幅
	float windowHeight_ = 0.0f; //画面の高さ
	TransformData transformData_ = { {1.0f,1.0f,1.0f,},{},{0.0f,0.0f,-10.0f} };//トランスフォームデータ
	Matrix4x4 worldMatrix_ = Matrix4x4::Indentity4x4();//ワールド行列
	Matrix4x4 viewMatrix_ = Matrix4x4::Indentity4x4();//ビュー行列
	Matrix4x4 projectionMatrix_ = Matrix4x4::Indentity4x4();//射影行列
	Matrix4x4 viewProjectionMatrix_ = Matrix4x4::Indentity4x4();//ビュー射影行列
	Matrix4x4 viewportMatrix_ = Matrix4x4::Indentity4x4();//ビューポート行列
};

