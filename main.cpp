#include <Novice.h>
#include <cmath>
#include "math.h"

const char kWindowTitle[] = "MT4_01_04_Basic";

struct Vector3 {
	float x, y, z;
};

struct Quaternion {
	float x, y, z, w;
};

struct Matrix4x4 {
	float m[4][4];
};

Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	result.x = float(v.x / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.y = float(v.y / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.z = float(v.z / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));

	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(
	const Vector3& axis, float angle) {
	Vector3 normAxis = Normalize(axis);
	float sinHalfAngle = std::sin(angle / 2.0f);
	float cosHalfAngle = std::cos(angle / 2.0f);
	return { normAxis.x * sinHalfAngle, normAxis.y * sinHalfAngle, normAxis.z * sinHalfAngle, cosHalfAngle };
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {
	return {
		lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
		lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w,
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
	};
}

Vector3 RotateVector(const Vector3& vector, const Quaternion&
	quaternion) {
	Quaternion qVector = { vector.x, vector.y, vector.z, 0.0f };
	Quaternion qConjugate = { -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
	Quaternion qResult = Multiply(Multiply(quaternion, qVector), qConjugate);
	return { qResult.x, qResult.y, qResult.z };
}

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {
	Matrix4x4 matrix = {};

	float xx = quaternion.x * quaternion.x;
	float yy = quaternion.y * quaternion.y;
	float zz = quaternion.z * quaternion.z;
	float xy = quaternion.x * quaternion.y;
	float xz = quaternion.x * quaternion.z;
	float yz = quaternion.y * quaternion.z;
	float wx = quaternion.w * quaternion.x;
	float wy = quaternion.w * quaternion.y;
	float wz = quaternion.w * quaternion.z;

	matrix.m[0][0] = 1.0f - 2.0f * (yy + zz);
	matrix.m[0][1] = 2.0f * (xy - wz);
	matrix.m[0][2] = 2.0f * (xz + wy);
	matrix.m[0][3] = 0.0f;

	matrix.m[1][0] = 2.0f * (xy + wz);
	matrix.m[1][1] = 1.0f - 2.0f * (xx + zz);
	matrix.m[1][2] = 2.0f * (yz - wx);
	matrix.m[1][3] = 0.0f;

	matrix.m[2][0] = 2.0f * (xz - wy);
	matrix.m[2][1] = 2.0f * (yz + wx);
	matrix.m[2][2] = 1.0f - 2.0f * (xx + yy);
	matrix.m[2][3] = 0.0f;

	matrix.m[3][0] = 0.0f;
	matrix.m[3][1] = 0.0f;
	matrix.m[3][2] = 0.0f;
	matrix.m[3][3] = 1.0f;

	matrix = Transpose(matrix);

	return matrix;
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.03f",
				matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

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
	float k = { 4.0f };

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

		Quaternion rotation = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 1.0f, 0.4f, -0.2f }), 0.45f);
		Vector3 pointY = { 2.1f, -0.9f, 1.3f };
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
		Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
		Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);

		QuaternionScreenPrintf(0, kRowHeight * 0, rotation, "   : rotation");
		MatrixScreenPrintf(0, kRowHeight * 1, rotateMatrix, "rotateMatrix");
		VectorScreenPrintf(0, kRowHeight * 6, rotateByQuaternion, "   : rotateByQuaternion");
		VectorScreenPrintf(0, kRowHeight * 7, rotateByMatrix, "   : rotateByMatrix");

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
