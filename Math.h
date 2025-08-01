#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

/// <summary>
/// 数学
/// </summary>
class Math {
public://メンバ関数
	/// <summary>
    /// コンストラクタ
    /// </summary>
	Math() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Math() = default;

	/// <summary>
	/// コタンジェント(余接)
	/// </summary>
	/// <param name="theta">θ</param>
	/// <returns>コタンジェント(余接)</returns>
	static float Cotangent(float theta);

	/// <summary>
	/// トランスフォーム
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <param name="matrix">行列</param>
	/// <returns>座標変換</returns>
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// トランスフォームノーマル(4x4の行列から平行移動を打ち消したもの)
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	static Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);
};

