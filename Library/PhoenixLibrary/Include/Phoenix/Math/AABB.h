#pragma once

#include "Phoenix/Math/Matrix.h"
#include "Phoenix/Math/Vector.h"


namespace Phoenix
{
	namespace Math
	{
		//****************************************************************************
		// バウンディングボックス
		//****************************************************************************
		class AABB
		{
		public:
			Vector3 min; // 最小値
			Vector3 max; // 最大値

			static const AABB Zero; // ゼロ

		public:
			AABB() {}
			AABB(const Vector3& min, const Vector3& max) { this->min = min; this->max = max; }
			~AABB() {}

		public:
			// AABBの範囲をリセットします
			void Reset();

			// 与えられた行列を元にAABBの範囲を設定します
			void Transform(const Matrix& transform);

			// 与えられたAABBを含むように範囲を拡張します
			void Extend(const AABB& aabb);

			// 与えられた点を含むように範囲を拡張します
			void Extend(const Vector3& point);

			// 与えられた点が範囲内に含まれているか判定します
			bool Contain(const Vector3& point);

			// AABBのコーナー位置を取得します
			void GetCorners(Vector3 corners[8]);

			// AABBの中心位置を取得します
			Vector3 GetCenter() const { return (min + max) / 2.0f; }

			// 空か
			bool IsEmpty() const { return min == max; }

			// 球との交差判定
			bool Intersect(const Math::Vector3& center, f32 radius) const;

			// AABBとの交差判定
			bool Intersect(const Math::AABB& aabb) const;
		};

	} // namespace Math
} // namespace Phoenix