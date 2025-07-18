#include "Vector3.h"
#include <cmath>

//加算
Vector3 Vector3::operator+(const Vector3& v) {
	Vector3 result = {};
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	return result;
}

//減算
Vector3 Vector3::operator-(const Vector3& v) {
	Vector3 result = {};
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	return result;
}

//スカラー倍
Vector3 Vector3::operator*(float n) {
	Vector3 result = {};
	result.x = x * n;
	result.y = y * n;
	result.z = z * n;
	return result;
}

//内積
float Vector3::Dot(const Vector3& v) {
	return x * v.x + y * v.y + z * v.z;
}

//長さ(ノルム)
float Vector3::Length() {
	float len = this->Dot(*this);
	return std::sqrt(len);
}

//正規化
Vector3 Vector3::Normalize() {
	Vector3 result = {};
	float len = this->Length();
	if (len != 0.0f) {
		result.x = x / len;
		result.y = y / len;
		result.z = z / len;
	}
	return result;
}
