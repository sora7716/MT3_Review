#pragma once
//4x4の行列
struct Matrix4x4 {
	float m[4][4];

	//加算
	Matrix4x4 operator+(const Matrix4x4& mat);
	//減算
	Matrix4x4 operator-(const Matrix4x4& mat);
	//乗算
	Matrix4x4 operator*(const Matrix4x4& mat);
	//逆行列
	Matrix4x4 operator~();
	//転置行列
	Matrix4x4 Transpose();
	//単位行列
	static Matrix4x4 Indentity4x4();
};
