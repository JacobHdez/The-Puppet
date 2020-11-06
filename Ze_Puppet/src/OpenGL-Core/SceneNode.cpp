#include "SceneNode.h"

SceneNode::SceneNode()
	: m_Parent(nullptr), m_Mesh(nullptr),
	  m_WorldTransform{ 1.0f }, m_Transform{ 1.0f }, m_ModelScale{ 1.0f },
	  m_Colour{ 0.7f, 0.7f, 0.7f }
{
}

SceneNode::SceneNode(Mesh* mesh, glm::vec3 colour)
	: m_Parent(nullptr),
	m_WorldTransform{ 1.0f }, m_Transform{ 1.0f }, m_ModelScale{ 1.0f }
{
	m_Mesh = mesh;
	m_Colour = colour;
}

SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < m_Children.size(); ++i)
	{
		delete m_Children[i];
	}
	m_Children.clear();
}

void SceneNode::AddChild(SceneNode* sn)
{
	m_Children.push_back(sn);
	sn->m_Parent = this;
}

void SceneNode::OnUpdate(float deltaTime)
{
	if (m_Parent)
	{
		m_WorldTransform = m_Parent->m_WorldTransform * m_Transform;
	}
	else
	{
		m_WorldTransform = m_Transform;
	}

	for (auto& it : m_Children)
	{
		it->OnUpdate(deltaTime);
	}
}

void SceneNode::Draw(Shader& shader)
{
	m_Mesh->Draw(shader);
}