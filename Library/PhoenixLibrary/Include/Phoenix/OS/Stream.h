#pragma once

#include <memory>
#include "Phoenix/Types.h"
#include "Phoenix/FND/Base.h"


namespace Phoenix
{
	namespace OS
	{
		//****************************************************************************
		// ストリームシーク
		//****************************************************************************
		enum class StreamSeek
		{
			Top,		// ファイルの先頭
			Current,	// ファイルの現在位置
			End			// ファイルの終端
		};

		//****************************************************************************
		// ファイルアクセス
		//****************************************************************************
		enum class FileAccess
		{
			Read,	// 読み込み
			Write,	// 書き込み
			Append	// 追加書き込み
		};

		//****************************************************************************
		// ストリーム操作インターフェース
		//****************************************************************************
		class IStream : public FND::Base
		{
		public:
			// クローズ
			virtual void Close() = 0;

			// 読み込み
			virtual s32 Read(void* buffer, s32 size) = 0;

			// 書き込み
			virtual s32 Write(const void* buffer, s32 size) = 0;

			// ポインタ位置設定
			virtual bool Seek(s32 offset, StreamSeek origin) = 0;

			// ポインタ位置取得
			virtual s32 Tell() = 0;

			// サイズ取得
			virtual s32 GetSize() = 0;
		};

		//****************************************************************************
		// ファイルストリーム操作インターフェース
		//****************************************************************************
		class IFileStream : public IStream
		{
		public:
			// ファイル生成
			static std::unique_ptr<IFileStream> Create();

			// 初期化
			virtual bool Initialize(const char* basePath) = 0;

			// 終了化
			virtual void Finalize() = 0;

			// 存在確認
			virtual bool Exists(const char* path) = 0;
			virtual bool ExistsW(const wchar_t* path) = 0;

			// オープン
			virtual bool Open(const char* path, FileAccess access) = 0;

			// ファイルの削除
			virtual bool Remove(const char* path) = 0;
		};

		//****************************************************************************
		// メモリストリーム操作インターフェース
		//****************************************************************************
		class IMemoryStream : public IStream
		{
		public:
			// ファイル生成
			static std::unique_ptr<IMemoryStream> Create();

			// 初期化
			virtual bool Initialize() = 0;

			// 終了化
			virtual void Finalize() = 0;

			// オープン
			virtual bool Open(void* buffer, s32 size) = 0;
		};
	} // namespace OS
} // namespace Phoenix