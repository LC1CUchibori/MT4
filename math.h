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
#define N 4 //�t�s������߂�s��̍s���E�� 
#include <math.h>

#include <iostream>

#define M_PI 3.14

struct Sphere {
	Vector3 center; // !< ���S�_
	float radius;   // !< ���a
};
struct Line {
	Vector3 origin; // !<�n�_
	Vector3 diff;   // !<�I�_�ւ̍����x�N�g��
};
struct Ray {
	Vector3 origin; // !<�n�_
	Vector3 diff;   // !<�I�_�ւ̍����x�N�g��
};
struct Segment {
	Vector3 origin; // !<�n�_
	Vector3 diff;   // !<�I�_�ւ̍����x�N�g��
};
struct Plane {
	Vector3 normal; //!< �@��
	float distance; //!< ����
};
struct Triangle
{
	Vector3 vertices[3];//!< ���_
};
struct AABB {
	Vector3 min; //!<�ŏ��_
	Vector3 max; //!<�ő�_
};
struct Vector2Int {
	int x;
	int y;
};
struct OBB {
	Vector3 center; //!<���S�_
	Vector3 orientations[3]; //!<���W���A���K���C����K�{
	Vector3 size; //!< ���W�����̒����̔����B���S����ʂ܂ł̋���
};
struct Spring {
	// �A���J�[�B�Œ肳�ꂽ�[�̈ʒu
	Vector3 anchor;
	float naturalLength;// ���R��
	float stiffness;// �����B�΂˒萔k
	float dampingCoefficient;// �����W��
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
	Vector3 anchor;// �A���J�[�|�C���g�B�Œ肳�ꂽ�[�̈ʒu
	float length; //�R�̒���
	float angle; //���݂̊p�x
	float angularVelocity;//�p���x
	float angularAcceleration;//�p�����x
};
struct ConicalPendulum {
	Vector3 anchor;// �A���J�[�|�C���g�B�Œ肳�ꂽ�[�̈ʒu
	float length; //�R�̒���
	float halfApexAngle;// �~���̒��p�̔���
	float angle; //���݂̊p�x
	float angularVelocity;//�p���x
};
struct Capsule {
	Segment segment;
	float radius;
};
// ���Z
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
// ���Z
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
// �X�J���[�{
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}
// ����
float Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}
// �����i�m�����j
float Length(const Vector3& v) {
	float result;
	result = float(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	return result;
}
// ���K��
Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	result.x = float(v.x / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.y = float(v.y / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.z = float(v.z / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));

	return result;
}
// �x�N�g���̑傫����2����v�Z����֐�
float MagnitudeSquared(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}
// �x�N�g���Ԃ̋������v�Z����֐�
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
// �s��̉��@
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;

}
// �s��̌��@
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

// �]�u�s��
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[j][i] = m.m[i][j];
		}
	}
	return result;
}