#pragma once


class IndexBuffer
{
private:	
	unsigned int m_Renderer;
	unsigned int m_Count;
public:
	IndexBuffer(unsigned int count, const unsigned int* data);
	~IndexBuffer();
	void Bind()  const;
	void Unbind()  const;

	inline unsigned int GetCount() const { return m_Count; }
};

