class CStreamDriverBuffer: public CSingleton<CStreamDriverBuffer>
{
	friend class CSingleton<CStreamDriverBuffer>;
protected:
	CStreamDriverBuffer() {}
public:
	void Read(__UINT8* &source, __UINT8* sink, int length)
	{
		memcpy(sink, source, length );
		source += length;
	}
	void Write(__UINT8* &source, __UINT8* sink, int length)
	{
		memcpy(source, sink, length );
		source += length;
	}
};

template <>
class CReaderStream<CStreamDriverBuffer>: public IReadableStream, public CStreamBase
{
public:
	virtual bool IsKindOfStream(const char *name) {return (strcmp(name, "CReaderStream_CStreamDriverBuffer")==0);}
	CReaderStream(const char* name, __UINT8* input, __UINT32 size, bool CloneBuffer): CStreamBase(name) 
	{
		m_pDriver = CStreamDriverBuffer::GetInstance();
		m_iBufferLength = size;
		if (CloneBuffer)
		{
			m_pBuffer = new __UINT8[m_iBufferLength];
			memcpy(m_pBuffer, input, size);
		}
		else
		{
			m_pBuffer = input;
		}
		m_pBufferPointer = m_pBuffer;
		m_isRefBuffer = !CloneBuffer;
	}
	virtual ~CReaderStream()
	{
		if (!m_isRefBuffer)
		{
			SAFE_DEL(m_pBuffer);
		}
	}
	void Read(__UINT8* buffer, int offset, int length) 
	{
		m_pDriver->Read(m_pBufferPointer, buffer + offset, length);
	}
	void ReadInt8(__INT8 &val) 
	{
		__UINT8 tmp = 0;
		m_pDriver->Read(m_pBufferPointer, &tmp, 1);
		val = __INT8(tmp);
	}
	void ReadUInt8(__UINT8 &val)
	{
		m_pDriver->Read(m_pBufferPointer, &val, 1);
	}
	void ReadInt16(__INT16 &val)
	{
		__UINT8 buf[2];
		m_pDriver->Read(m_pBufferPointer, buf, 2);
		val = __UINT16(buf[1]);
		val <<= 8;
		val |= __UINT16(buf[0]);
	}
	void ReadUInt16(__UINT16 &val)
	{
		val = 0;
		__INT16 tmp = 0;
		ReadInt16(tmp);
		val = __UINT16(tmp);
	}
	void ReadInt32(__INT32 &val)
	{
		val = 0;
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buf[4];
			m_pDriver->Read(m_pBufferPointer, buf, 4);
			val = __UINT16(buf[3]);
			val <<= 8;
			val |= __UINT16(buf[2]);
			val <<= 8;
			val |= __UINT16(buf[1]);
			val <<= 8;
			val |= __UINT16(buf[0]);
		}
	}
	void ReadUInt32(__UINT32 &val) 
	{
		val = 0;
		__INT32 tmp = 0;
		ReadInt32(tmp);
		val = __UINT32(tmp);
	}
	void ReadInt64(__INT64 &val)
	{
		val = 0;
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buf[8];
			m_pDriver->Read(m_pBufferPointer, buf, 8);
			val = __UINT16(buf[7]);
			val <<= 8;
			val |= __UINT16(buf[6]);
			val <<= 8;
			val |= __UINT16(buf[5]);
			val <<= 8;
			val |= __UINT16(buf[4]);
			val <<= 8;
			val |= __UINT16(buf[3]);
			val <<= 8;
			val |= __UINT16(buf[2]);
			val <<= 8;
			val |= __UINT16(buf[1]);
			val <<= 8;
			val |= __UINT16(buf[0]);
		}
	}
	void ReadUInt64(__UINT64 &val)
	{
		val = 0;
		__INT64 tmp = 0;
		ReadInt64(tmp);
		val = __UINT64(tmp);
	}
	void Skip(__UINT32 n)
	{
		m_pBufferPointer += n;
	}
	void Goto(__UINT32 pos)
	{
		m_pBufferPointer = m_pBuffer + pos;
	}
	__UINT32 GetLength()
	{
		return m_iBufferLength;
	}

protected:
	CStreamDriverBuffer* m_pDriver;
	__UINT8* m_pBuffer;
	__UINT8* m_pBufferPointer;
	__UINT32 m_iBufferLength;
	bool m_isRefBuffer;
};

template <>
class CWriterStream<CStreamDriverBuffer>: public IWritableStream, public CStreamBase
{
public:
	virtual bool IsKindOfStream(const char *name) {return (strcmp(name, "CReaderStream_CStreamDriverBuffer")==0);}
	CWriterStream(const char* name, __UINT8* input, __UINT32 size, bool CloneBuffer): CStreamBase(name) 
	{
		m_pDriver = CStreamDriverBuffer::GetInstance();
		m_iBufferLength = size;
		if (CloneBuffer)
		{
			m_pBuffer = new __UINT8[m_iBufferLength];
			memcpy(m_pBuffer, input, size);
		}
		else
		{
			m_pBuffer = input;
		}
		m_pBufferPointer = m_pBuffer;
		m_isRefBuffer = !CloneBuffer;
	}
	virtual ~CWriterStream()
	{
		if (!m_isRefBuffer)
		{
			SAFE_DEL(m_pBuffer);
		}
	}
	void Write(__UINT8* buffer, int offset, int length) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			m_pDriver->Write(m_pBufferPointer, buffer + offset, length);
		}
	}
	void WriteInt8(__INT8 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val)};
			m_pDriver->Write(m_pBufferPointer, buffer , 1);
		}
	}
	void WriteUInt8(__UINT8 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val)};
			m_pDriver->Write(m_pBufferPointer, buffer , 1);
		}
	}
	void WriteInt16(__INT16 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8(val>>8)};
			m_pDriver->Write(m_pBufferPointer, buffer , 2);
		}
	}
	void WriteUInt16(__UINT16 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8((val>>8)&0xFF)};
			m_pDriver->Write(m_pBufferPointer, buffer , 2);
		}
	}
	void WriteInt32(__INT32 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8((val>>8)&0xFF), 
				__UINT8((val>>16)&0xFF), __UINT8((val>>24)&0xFF)};
			m_pDriver->Write(m_pBufferPointer, buffer , 4);
		}
	}
	void WriteUInt32(__UINT32 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8((val>>8)&0xFF), 
				__UINT8((val>>16)&0xFF), __UINT8((val>>24)&0xFF)};
			m_pDriver->Write(m_pBufferPointer, buffer , 4);
		}
	}
	void WriteInt64(__INT64 val) 
	{
		TODO("WriteInt64 is not implemented");
	}
	void WriteUInt64(__UINT64 val) 
	{
		TODO("WriteUInt64 is not implemented");
	}
	void WriteSeq(__UINT8 val, int length) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 *buffer = new __UINT8[length];
			memset(buffer, 0, length);
			m_pDriver->Write(m_pBufferPointer, buffer , length);
			SAFE_DEL(buffer);
		}
	}
protected:
	CStreamDriverBuffer* m_pDriver;
	__UINT8* m_pBuffer;
	__UINT8* m_pBufferPointer;
	__UINT32 m_iBufferLength;
	bool m_isRefBuffer;
};