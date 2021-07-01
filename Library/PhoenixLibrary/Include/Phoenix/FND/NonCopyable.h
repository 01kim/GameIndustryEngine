#pragma once


namespace Phoenix
{
	namespace FND
	{
		//****************************************************************************
		// 継承したクラスをコピー不可にする
		//****************************************************************************
		class NonCopyable
		{
		protected:
			NonCopyable() {}
			~NonCopyable() {}
		private:
			NonCopyable(const NonCopyable&);
			const NonCopyable& operator =(const NonCopyable&);
		};

	}	// namespace FND
}	// namespace Phoenix
