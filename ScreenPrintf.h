#pragma once
#include "Vector3.h"

//スクリーンプリント
class ScreenPrintf {
public://メンバ変数
	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static ScreenPrintf* GetInstance();

	/// <summary>
	/// ベクトルのスクリーンプリント
	/// </summary>
	/// <param name="x">x</param>
	/// <param name="y">y</param>
	/// <param name="vector">ベクトル</param>
	/// <param name="label">ラベル</param>
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();
private://静的メンバ変数
	//インスタンス
	static inline ScreenPrintf* instance = nullptr;
	//解放したかどうか
	static inline bool isFinalize = false;
	//列の幅
	static inline const int kColumnWidth = 60;
private://メンバ変数
};

