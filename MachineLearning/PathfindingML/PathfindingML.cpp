#include "PathfindingML.h"

#include "../Texture/Texture.h"
#include "../Renderer/Renderer.h"

PathfindingML::PathfindingML()
	: m_AI{ 0,0,0 } /*I'm lazy TODO: Make this better, lazy bastard*/
{
	m_Nodes.push_back(new Node{ MathUtils::Point2f{200.f, 100.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 0, 0.f });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{300.f, 150.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 1, 40.f });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{100.f, 150.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 2, 0.f });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{300.f, 250.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 3, 80.f });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{300.f, 350.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 4, 100.f });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{100.f, 250.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 5, 0.f });

	m_Transitions.push_back(new Transition{ m_Nodes[0], m_Nodes[1] });
	m_Transitions.push_back(new Transition{ m_Nodes[1], m_Nodes[0] });

	m_Transitions.push_back(new Transition{ m_Nodes[0], m_Nodes[2] });
	m_Transitions.push_back(new Transition{ m_Nodes[2], m_Nodes[0] });

	m_Transitions.push_back(new Transition{ m_Nodes[2], m_Nodes[5] });
	m_Transitions.push_back(new Transition{ m_Nodes[5], m_Nodes[2] });

	m_Transitions.push_back(new Transition{ m_Nodes[3], m_Nodes[4] });
	m_Transitions.push_back(new Transition{ m_Nodes[4], m_Nodes[3] });

	m_Transitions.push_back(new Transition{ m_Nodes[1], m_Nodes[3] });
	m_Transitions.push_back(new Transition{ m_Nodes[3], m_Nodes[1] });

	m_AI = PathfindingAI{ m_Nodes.size(), 0, 4 };

	FMatrix rewardMatrix{ m_Nodes.size(),m_Nodes.size(), -1.f };

	for (size_t r{}; r < rewardMatrix.GetNumberOfRows(); ++r)
		for (Transition* pTransition : m_Nodes[r]->GetTransitions())
			rewardMatrix.Set(pTransition->GetFromNode()->GetIndex(), pTransition->GetToNode()->GetIndex(), 0.f);

	rewardMatrix.Set(3, 4, 100.f); // manually set goal transition to 100.f

	rewardMatrix.Print(); // for debugging purposes

	m_AI.SetRewardMatrix(std::move(rewardMatrix));

	m_AI.SetNodes(&m_Nodes);
	m_AI.SetTransitions(&m_Transitions);
}

PathfindingML::~PathfindingML()
{
	for (Node* pNode : m_Nodes)
		delete pNode;

	for (Transition* pTransition : m_Transitions)
		delete pTransition;
}

void PathfindingML::Update() noexcept
{
	return m_AI.Train();
}

void PathfindingML::Render() const noexcept
{
	for (Node* const pNode : m_Nodes)
		pNode->Render();

	for (Transition* const pTransition : m_Transitions)
		pTransition->SetIsRendered(false);
}
