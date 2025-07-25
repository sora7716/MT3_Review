#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

/// <summary>
/// レンダリング
/// </summary>
class Rendering{
public://メンバ関数
	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static Rendering* GetInstance();

	/// <summary>
	/// 拡縮の行列の作成
	/// </summary>
	/// <param name="scale">拡縮</param>
	/// <returns>拡縮の行列</returns>
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// 平行移動の行列の作成
	/// </summary>
	/// <param name="translate">平行移動</param>
	/// <returns>平行移動の行列</returns>
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

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

