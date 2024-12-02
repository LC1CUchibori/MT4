#pragma once

#define NOMINMAX
#include <limits>
#include <Novice.h>
#include <Matrix4x4.h>
#include <Vector2.h>
#include <Vector3.h>
#include <assert.h>
#include <cmath>
#include <algorithm>
#define N 4 //逆行列を求める行列の行数・列数 
#include <math.h>

#include <iostream>

#define M_PI 3.14

struct Sphere {
	Vector3 center; // !< 中心点
	float radius;   // !< 半径
};
struct Line {
	Vector3 origin; // !<始点
	Vector3 diff;   // !<終点への差分ベクトル
};
struct Ray {
	Vector3 origin; // !<始点
	Vector3 diff;   // !<終点への差分ベクトル
};
struct Segment {
	Vector3 origin; // !<始点
	Vector3 diff;   // !<終点への差分ベクトル
};
struct Plane {
	Vector3 normal; //!< 法線
	float distance; //!< 距離
};
struct Triangle
{
	Vector3 vertices[3];//!< 頂点
};
struct AABB {
	Vector3 min; //!<最小点
	Vector3 max; //!<最大点
};
struct Vector2Int {
	int x;
	int y;
};
struct OBB {
	Vector3 center; //!<中心点
	Vector3 orientations[3]; //!<座標軸、正規化，直交必須
	Vector3 size; //!< 座標方向の長さの半分。中心から面までの距離
};
struct Spring {
	// アンカー。固定された端の位置
	Vector3 anchor;
	float naturalLength;// 自然長
	float stiffness;// 剛性。ばね定数k
	float dampingCoefficient;// 減衰係数
};
struct Ball {
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;
	float radius;
	unsigned int color;

};
struct Pendulum {
	Vector3 anchor;// アンカーポイント。固定された端の位置
	float length; //紐の長さ
	float angle; //現在の角度
	float angularVelocity;//角速度
	float angularAcceleration;//角加速度
};
struct ConicalPendulum {
	Vector3 anchor;// アンカーポイント。固定された端の位置
	float length; //紐の長さ
	float halfApexAngle;// 円錐の頂角の半分
	float angle; //現在の角度
	float angularVelocity;//角速度
};
struct Capsule {
	Segment segment;
	float radius;
};
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}
// 内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}
// 長さ（ノルム）
float Length(const Vector3& v) {
	float result;
	result = float(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	return result;
}
// 正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	result.x = float(v.x / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.y = float(v.y / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.z = float(v.z / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));

	return result;
}
// ベクトルの大きさの2乗を計算する関数
float MagnitudeSquared(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}
// ベクトル間の距離を計算する関数
float Distance(const Vector3& a, const Vector3& b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}
int check(double mat[N][N], double inv[N][N]) {

	double inner_product;
	int i, j, k;
	double ans;
	double diff;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			inner_product = 0;
			for (k = 0; k < N; k++) {
				inner_product += mat[i][k] * inv[k][j];
			}

			ans = (i == j) ? 1 : 0;
			diff = ans - inner_product;


		}
	}

	return 1;
}
// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;

}
// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[j][i] = m.m[i][j];
		}
	}
	return result;
}