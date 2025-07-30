#pragma once

//三次元のベクトル	
struct Vector3 {
	float x;
	float y;
	float z;

	//加算
	Vector3 operator+(const Vector3& v);
	//減算
	Vector3 operator-(const Vector3& v);
	//スカラー倍
	Vector3 operator*(float n);

	/// <summary>
	/// 内積
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>内積</returns>
	float Dot(const Vector3& v);

	/// <summary>
	/// 長さ(ノルム)
	/// </summary>
	/// <returns>長さ(ノルム)</returns>
	float Length();

	/// <summary>
	/// 正規化
	/// </summary>
	/// <returns>正規化</returns>
	Vector3 Normalize();

	/// <summary>
	/// クロス積
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>クロス積</returns>
	Vector3 Cross(const Vector3& v);
};