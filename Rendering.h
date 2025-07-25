#pragma once
#include "RenderingData.h"
#include "Matrix4x4.h"

/// <summary>
/// レンダリング
/// </summary>
class Rendering {
public://メンバ関数
	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static Rendering* GetInstance();

	/// <summary>
	/// 拡縮行列の作成
	/// </summary>
	/// <param name="scale">拡縮</param>
	/// <returns>拡縮行列</returns>
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
    /// X軸の回転行列の作成
    /// </summary>
    /// <param name="theta">θ</param>
    /// <returns>x軸の回転行列</returns>
	Matrix4x4 MakeRotateXMatrix(float theta);

	/// <summary>
	/// Y軸の回転行列の作成
	/// </summary>
	/// <param name="theta">θ</param>
	/// <returns>Y軸の回転行列</returns>
	Matrix4x4 MakeRotateYMatrix(float theta);

	/// <summary>
	/// Z軸の回転行列の作成
	/// </summary>
	/// <param name="theta">θ</param>
	/// <returns>Z軸の回転行列</returns>
	Matrix4x4 MakeRotateZMatrix(float theta);

	/// <summary>
	/// 回転行列の作成
	/// </summary>
	/// <param name="rotate">回転</param>
	/// <returns>回転行列</returns>
	Matrix4x4 MakeRotateMatrix(const Vector3& rotate);

	/// <summary>
	/// 平行移動行列の作成
	/// </summary>
	/// <param name="translate">平行移動</param>
	/// <returns>平行移動行列</returns>
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// アフィン行列の作成
	/// </summary>
	/// <param name="transformData">トランスフォームデータ</param>
	/// <returns>アフィン行列</returns>
	Matrix4x4 MakeAffineMatrix(const TransformData& transformData);

	/// <summary>
	/// 座標変換
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <param name="matrix">行列</param>
	/// <returns>座標変換</returns>
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();
private://静的メンバ変数
	//インスタンス
	static inline Rendering* instance = nullptr;
	//解放したかどうか
	static inline bool isFinalize = false;
private://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Rendering() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Rendering() = default;
};

