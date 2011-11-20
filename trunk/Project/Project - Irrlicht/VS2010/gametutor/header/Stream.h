#ifndef __ISTREAM_H__
#define __ISTREAM_H__

#include "Header.h"
#include "CSingleton.h"
namespace GameTutor
{
	class IReadableStream
	{
	public:
		virtual void Read(__UINT8* buffer, int offset, int length) = 0;
		virtual void ReadInt8(__INT8 &val) = 0;
		virtual void ReadUInt8(__UINT8 &val) = 0;
		virtual void ReadInt16(__INT16 &val) = 0;
		virtual void ReadUInt16(__UINT16 &val) = 0;
		virtual void ReadInt32(__INT32 &val) = 0;
		virtual void ReadUInt32(__UINT32 &val) = 0;
		virtual void ReadInt64(__INT64 &val) = 0;
		virtual void ReadUInt64(__UINT64 &val) = 0;
		virtual void Skip(__UINT32 n) = 0;
		virtual void Goto(__UINT32 pos) = 0;
		virtual __UINT32 GetLength() = 0;
		virtual bool IsEndOfStream() = 0;
		virtual __INT32 GetCurrentPosition() = 0;
	};

	class IWritableStream
	{
	public:
		virtual void Write(__UINT8* buffer, int offset, int length) = 0;
		virtual void WriteInt8(__INT8 val) = 0;
		virtual void WriteUInt8(__UINT8 val) = 0;
		virtual void WriteInt16(__INT16 val) = 0;
		virtual void WriteUInt16(__UINT16 val) = 0;
		virtual void WriteInt32(__INT32 val) = 0;
		virtual void WriteUInt32(__UINT32 val) = 0;
		virtual void WriteInt64(__INT64 val) = 0;
		virtual void WriteUInt64(__UINT64 val) = 0;
		virtual void WriteSeq(__UINT8 val, int length) = 0;
	};

	enum EStreamStatus {
		ESTREAM_READY,
		ESTREAM_ERROR,
		ESTREAM_OPEN,
		ESTREAM_CLOSE
	};

	class CStreamBase
	{
	public:
		CStreamBase(const char* name):m_eStreamStatus(ESTREAM_READY)
		{
			m_strName = new char[strlen(name) + 1];
			memcpy(m_strName, name, strlen(name) + 1);
		}
		virtual ~CStreamBase()
		{
			SAFE_DEL(m_strName);
		}
		virtual void Open() {m_eStreamStatus = ESTREAM_OPEN;}
		virtual void Close() {m_eStreamStatus = ESTREAM_CLOSE;}
		virtual char* GetName() {return m_strName;}
		virtual EStreamStatus GetStatus() {return m_eStreamStatus;}
		virtual bool IsKindOfStream(const char *name) {return (strcmp(name, "IStreamBase")==0);}
		bool IsReadableStream()
		{
			IReadableStream *stream = dynamic_cast<IReadableStream *>(this);
			return stream != 0;
		}
		bool IsWritableStream()
		{
			IWritableStream *stream = dynamic_cast<IWritableStream *>(this);
			return stream != 0;
		}
	protected:
		EStreamStatus m_eStreamStatus;
		char* m_strName;
	};


	template <class StreamDriver>
	class CReaderStream: public IReadableStream, public CStreamBase
	{
	public:
		CReaderStream(const char* name): CStreamBase(name) {}
		virtual ~CReaderStream(){}
		virtual void Read(__UINT8* buffer, int offset, int length) {}
		virtual void ReadInt8(__INT8 &val) {}
		virtual void ReadUInt8(__UINT8 &val) {}
		virtual void ReadInt16(__INT16 &val) {}
		virtual void ReadUInt16(__UINT16 &val) {}
		virtual void ReadInt32(__INT32 &val) {}
		virtual void ReadUInt32(__UINT32 &val) {}
		virtual void ReadInt64(__INT64 &val) {}
		virtual void ReadUInt64(__UINT64 &val) {}
		virtual void Skip(__UINT32 n) {}
		virtual void Goto(__UINT32 pos) {}
		virtual void Open() {CStreamBase::Open();}
		virtual void Close() {CStreamBase::Close();}
		virtual __UINT32 GetLength() {return 0;}
		virtual bool IsEndOfStream() {return true;}
		virtual bool IsKindOfStream(const char *name) {return (strcmp(name, "CReaderStream")==0);}
		virtual __INT32 GetCurrentPosition() {return 0;}
	};

	template <class StreamDriver>
	class CWriterStream: public IWritableStream, public CStreamBase
	{
	public:
		CWriterStream(const char* name): CStreamBase(name) {}
		virtual ~CWriterStream(){}
		virtual void Write(__UINT8* buffer, int offset, int length) {}
		virtual void WriteInt8(__INT8 val) {}
		virtual void WriteUInt8(__UINT8 val) {}
		virtual void WriteInt16(__INT16 val) {}
		virtual void WriteUInt16(__UINT16 val) {}
		virtual void WriteInt32(__INT32 val) {}
		virtual void WriteUInt32(__UINT32 val) {}
		virtual void WriteInt64(__INT64 val) {}
		virtual void WriteUInt64(__UINT64 val) {}
		virtual void WriteSeq(__UINT8 val, int length) {}
		virtual void Open() {CStreamBase::Open();}
		virtual void Close() {CStreamBase::Close();}
		virtual __UINT32 GetLength() {return 0;}
		virtual bool IsKindOfStream(const char *name) {return (strcmp(name, "CWriterStream")==0);}
	};

#include "Stream_FileWin32.h"
#include "Stream_Buffer.h"
}
#endif