#pragma once

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
};

