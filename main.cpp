#include <Novice.h>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>

const char kWindowTitle[] = "MT4";

struct Vector3 {
	float x, y, z;
};

struct Quaternion {
	float x, y, z, w;
};

Quaternion IdentityQuaternion() { 

	//資料p8を参考にする。wだけに1を入れてそれ以外を0にするだけ

}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {

	//資料p7を参考にする。1行ごとに分けて考えること。(何もなし=w、i=x,j=y,k=z)
	//必ず、x,y,z,wの値に分かれます。1つに合成しないこと。。
}

Quaternion Conjugate(const Quaternion& quaternion) {

	//p9を参考にする。w以外にマイナスを付けるだけ。
}

float Norm(const Quaternion& quaternion) {

	//p10を参考にする。Vector3でやったようなLnegthの式にwの2乗が追加されているだけ。
}

Quaternion Normalize(const Quaternion& quaternion) {

	//p11を参考にする。Vector3のNomalizeにwが増えただけ。
}
Quaternion Inverse(const Quaternion& quaternion) {
	//p12を参考にする。上記のNormalizeのlengthに該当する値をlengthの二乗に、クオータニオンに該当していた値をクオータニオンの共役に変えるだけ。
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