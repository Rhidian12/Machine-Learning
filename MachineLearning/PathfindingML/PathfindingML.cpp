#include "PathfindingML.h"

#include "../Texture/Texture.h"
#include "../Renderer/Renderer.h"

PathfindingML::PathfindingML()
	: m_AI{ 0,0,0 }
{
	MathUtils::RGBColour startColour{ 0.f, 255.f, 0.f };
	MathUtils::RGBColour standardColour{ 100.f, 100.f, 100.f };
	MathUtils::RGBColour endColour{ 255.f, 0.f, 0.f };

	m_Nodes.push_back(new Node{ MathUtils::Point2f{200.f, 100.f},	 startColour,		0 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{300.f, 150.f},	 standardColour,	1 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{100.f, 150.f},	 standardColour,	2 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{300.f, 250.f},	 standardColour,	3 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{300.f, 350.f},	 standardColour,	4 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{100.f, 250.f},	 standardColour,	5 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{400.f, 100.f},	 standardColour,	6 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{400.f, 150.f},	 standardColour,	7 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{500.f, 150.f},	 standardColour,	8 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{100.f, 50.f},	 standardColour,	9 });
	m_Nodes.push_back(new Node{ MathUtils::Point2f{400.f, 250.f},	 endColour,			10 });

#pragma region Transitions
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

	m_Transitions.push_back(new Transition{ m_Nodes[0], m_Nodes[9] });
	m_Transitions.push_back(new Transition{ m_Nodes[9], m_Nodes[0] });

	m_Transitions.push_back(new Transition{ m_Nodes[1], m_Nodes[7] });
	m_Transitions.push_back(new Transition{ m_Nodes[7], m_Nodes[1] });

	m_Transitions.push_back(new Transition{ m_Nodes[7], m_Nodes[8] });
	m_Transitions.push_back(new Transition{ m_Nodes[8], m_Nodes[7] });

	m_Transitions.push_back(new Transition{ m_Nodes[7], m_Nodes[6] });
	m_Transitions.push_back(new Transition{ m_Nodes[6], m_Nodes[7] });

	m_Transitions.push_back(new Transition{ m_Nodes[6], m_Nodes[8] });
	m_Transitions.push_back(new Transition{ m_Nodes[8], m_Nodes[6] });

	m_Transitions.push_back(new Transition{ m_Nodes[7], m_Nodes[10] });
	m_Transitions.push_back(new Transition{ m_Nodes[10], m_Nodes[7] });

	m_Transitions.push_back(new Transition{ m_Nodes[3], m_Nodes[10] });
	m_Transitions.push_back(new Transition{ m_Nodes[10], m_Nodes[3] });
#pragma endregion

	m_AI = PathfindingAI{ m_Nodes.size(), 0, 10 };

	FMatrix rewardMatrix{ m_Nodes.size(),m_Nodes.size(), -1.f }; // default initialize the reward matrix with -1.f

	for (size_t r{}; r < rewardMatrix.GetNumberOfRows(); ++r)
		for (Transition* pTransition : m_Nodes[r]->GetTransitions())
			rewardMatrix.Set(pTransition->GetFromNode()->GetIndex(), pTransition->GetToNode()->GetIndex(), 0.f); // set all possible connections to 0.f

	rewardMatrix.Set(3, 10, 100.f); // manually set goal transition to 100.f
	rewardMatrix.Set(7, 10, 100.f); // manually set goal transition to 100.f

	//rewardMatrix.Print(); // for debugging purposes

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
	m_AI.Train();
}

void PathfindingML::Render() const noexcept
{
	for (Node* const pNode : m_Nodes)
		pNode->Render();

	for (Transition* const pTransition : m_Transitions)
		pTransition->SetIsRendered(false);
}
