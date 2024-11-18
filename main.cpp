#include <Novice.h>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>

const char kWindowTitle[] = "LE2D_03_ウチボリ_ユウタ_MT4";

struct Vector3 {
	float x, y, z;
};

struct Quaternion {
	float x, y, z, w;
};

Quaternion IdentityQuaternion() { 

	return {0.0f, 0.0f, 0.0f, 1.0f};
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {

	// クオータニオンの積
	return {
		lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y, // x
		lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x, // y
		lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w, // z
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z  // w
	};
}

Quaternion Conjugate(const Quaternion& quaternion) {

	// 共役: x, y, zを反転
	return {
		-quaternion.x,
		-quaternion.y,
		-quaternion.z,
		quaternion.w
	};
}

float Norm(const Quaternion& quaternion) {

	// ノルム（長さの二乗）
	return std::sqrt(quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z + 
		quaternion.w * quaternion.w);
}

Quaternion Normalize(const Quaternion& quaternion) {

	// ノルムの平方根を計算
	float length = std::sqrt(Norm(quaternion));
	assert(length != 0.0f && "Division by zero during normalization");
	// 正規化
	return {
		quaternion.x / length,
		quaternion.y / length,
		quaternion.z / length,
		quaternion.w / length
	};
}
Quaternion Inverse(const Quaternion& quaternion) {
	// 逆数 = 共役 / ノルムの二乗
	float normSquared = Norm(quaternion);
	assert(normSquared != 0.0f && "Division by zero during inversion");
	Quaternion conjugate = Conjugate(quaternion);
	return {
		conjugate.x / normSquared,
		conjugate.y / normSquared,
		conjugate.z / normSquared,
		conjugate.w / normSquared
	};
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void QuaternionScreenPrintf(int x, int y, Quaternion quaternion, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, label);
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1{ 1.0f, 3.0f, -5.0f };
	Vector3 v2{ 4.0f, -1.0f, 2.0f };
	//float k = { 4.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Quaternion q1 = { 2.0f, 3.0f, 4.0f, 1.0f };
		Quaternion q2 = { 1.0f, 3.0f, 5.0f, 2.0f };
		Quaternion identity = IdentityQuaternion();
		Quaternion conj = Conjugate(q1);
		Quaternion inv = Inverse(q1);
		Quaternion normal = Normalize(q1);
		Quaternion mul1 = Multiply(q1, q2);
		Quaternion mul2 = Multiply(q2, q1);
		float norm = Norm(q1);

		QuaternionScreenPrintf(0, kRowHeight * 0, identity, "   : Identity");
		QuaternionScreenPrintf(0, kRowHeight * 1, conj, "   : Conjugate");
		QuaternionScreenPrintf(0, kRowHeight * 2, inv, "   : Inverse");
		QuaternionScreenPrintf(0, kRowHeight * 3, normal, "   : Normalize");
		QuaternionScreenPrintf(0, kRowHeight * 4, mul1, "   : Multiply(q1, q2)");
		QuaternionScreenPrintf(0, kRowHeight * 5, mul2, "   : Multiply(q2, q1)");
		Novice::ScreenPrintf(0, kRowHeight * 6, "%.02f                          : Norm", norm);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}