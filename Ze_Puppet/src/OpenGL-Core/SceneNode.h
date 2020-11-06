#pragma once

#include "Mesh.h"
#include "glm/glm.hpp"
#include <vector>

class SceneNode
{
protected:
	SceneNode* m_Parent;
	Mesh* m_Mesh;
	glm::mat4 m_WorldTransform;
	glm::mat4 m_Transform;
	glm::vec3 m_ModelScale;
	glm::vec3 m_Colour;
	std::vector<SceneNode*> m_Children;
	glm::vec3 m_Pivot;
public:
	SceneNode();
	SceneNode(Mesh* mesh, glm::vec3 colour);
	~SceneNode();

	void SetTransform(const glm::mat4& transform) { m_Transform = transform; }
	const glm::mat4& GetTransform() const { return m_Transform; }
	glm::mat4 GetWorldTransform() const { return m_WorldTransform; }

	glm::vec3 GetColour() const { return m_Colour; }
	void SetColour(glm::vec3 colour) { m_Colour = colour; }

	glm::vec3 GetModelScale() const { return m_ModelScale; }
	void SetModelScale(glm::vec3 scale) { m_ModelScale = scale; }

	Mesh* GetMesh() const { return m_Mesh; }
	void SetMesh(Mesh* mesh) { m_Mesh = mesh; }

	void AddChild(SceneNode* sn);

	void OnUpdate(float deltaTime);
	void Draw(Shader& shader);

	std::vector<SceneNode*>::const_iterator GetChildIteratorBegin() { return m_Children.begin(); }
	std::vector<SceneNode*>::const_iterator GetChildIteratorEnd() { return m_Children.end(); }

	glm::vec3 GetPivot() const { return m_Pivot; }
	void SetPivot(glm::vec3 pivot) { m_Pivot = pivot; }
};