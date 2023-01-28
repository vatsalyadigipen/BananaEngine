#pragma once

#include <vector>
#include "Renderer.h"
#include "Logger/Logger.h"

struct VertexBufferElements
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeofType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElements> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		// Need to provide data type along with the Push()
		// instead of layoutObj->Push(ElementCount)
		// do this	  layoutObj->Push<float>(ElementCount);
		// or this	  layoutObj->Push<unsigned int>(ElementCount);
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferElements::GetSizeofType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElements::GetSizeofType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElements::GetSizeofType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElements>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};