#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"
#include <limits.h>

VertexArray::VertexArray()
	: m_RendererID(UINT_MAX) {}

VertexArray::~VertexArray()
{
	if (m_RendererID != UINT_MAX)
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Setup()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}