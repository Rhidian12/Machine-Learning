# Machine-Learning

### Introduction
This is a personal project to learn how Machine Learning works. I first recreated the Machine Learning as we saw in Gameplay Programming. I will later try to research some more complex Machine Learning.

### Pathfinding AI (Finished around 25/07)
We have a map consisting of nodes:

![Map](https://github.com/Rhidian12/Machine-Learning/blob/main/Markdown/Map.png)

The goal for the AI is to find the best path from the start node (in this case: 0) to the end node (in this case: 10).

The only information the AI has at any given time is the following:
* At which node it is right now
* To which nodes can it go
* Is one of the connected nodes the end node

The AI does this by accessing the reward matrix.
```cpp
  FMatrix rewardMatrix{ m_Nodes.size(),m_Nodes.size(), -1.f }; // default initialize the reward matrix with -1.f

  for (size_t r{}; r < rewardMatrix.GetNumberOfRows(); ++r)
	  for (Transition* pTransition : m_Nodes[r]->GetTransitions())
		  rewardMatrix.Set(pTransition->GetFromNode()->GetIndex(), pTransition->GetToNode()->GetIndex(), 0.f); // set all possible connections to 0.f

  rewardMatrix.Set(3, 10, 100.f); // manually set goal transition to 100.f
  rewardMatrix.Set(7, 10, 100.f); // manually set goal transition to 100.f
  ```
  
  The reward matrix contains 3 possible values: -1, 0 or 100. </br>
  -1 means there is no connection possible, 0 means there is a connection between the two nodes, 100 means that the connection leads to the end node.
  
  The actual learning happens in the Q matrix. Every time the AI traverses a node, it finds the previous maximum value of the Q matrix at that node. This previous value gets multiplied with a hyperparameter, which controls learning speed, and finally added to the value of transition in the reward matrix.
  
  ```cpp
  	// Select a random node (FROM)
	Node* const pFromNode{ (*m_pNodes)[rand() % m_pNodes->size()] };

	// select a valid TO node
	std::vector<Node*> possibleNodes{};
	for (Transition* pTransition : pFromNode->GetTransitions())
		if (m_RewardMatrix.Get(pFromNode->GetIndex(), pTransition->GetToNode()->GetIndex()) >= 0.f)
			possibleNodes.push_back(pTransition->GetToNode());

	Node* const pToNode{ possibleNodes[rand() % possibleNodes.size()] };

	// Calculate the max of row nr [TO NODE INDEX]
	const float maxOfRow{ m_QMatrix.GetMaxOfRow(pToNode->GetIndex()) };

	// Gather all the columns that have a value equal to max
	std::vector<uint32_t> columnIndices{};
	for (size_t i{}; i < m_QMatrix.GetNumberOfColumns(); ++i)
		if (m_QMatrix.Get(pToNode->GetIndex(), i) == maxOfRow)
			columnIndices.push_back(i);

	// Get the value from the random cell
	const float randomValueFromQMatrix{ m_QMatrix.Get(pToNode->GetIndex(), columnIndices[rand() % columnIndices.size()]) };

	// Update the value for the Q matrix
	const float qUpdate{ m_RewardMatrix.Get(pFromNode->GetIndex(), pToNode->GetIndex()) + m_Gamma * randomValueFromQMatrix };
	m_QMatrix.Set(pFromNode->GetIndex(), pToNode->GetIndex(), qUpdate);
  ```
  
  In the end, the AI needs hundreds of iterations to traverse all the nodes, but it will always find the fastest path from node 0 to node 10.</br>
  This is done by starting at our start node, and then traversing to the next node with the highest score in the Q matrix.
  
  ```cpp
  void PathfindingAI::Train() noexcept
{
	if (m_CurrentIteration < m_NrOfIterations) // we are still training
	{
		const float score{ Update() };

		std::cout << "Iteration: " << m_CurrentIteration++ << ", Score: " << score << std::endl;
	}
	else if (m_CurrentIteration == m_NrOfIterations) // end of training
	{
		// print Q matrix
		std::cout << "QMatrix:" << std::endl;
		m_QMatrix.Print();
		std::cout << std::endl;

		uint32_t location{ m_StartLocation };

		std::cout << "We start at index: " << location << std::endl;

		while (location != m_Goal)
		{
			const float maxOfRow{ m_QMatrix.GetMaxOfRow(location) };

			std::vector<uint32_t> columnIndices{};

			for (uint32_t c{}; c < m_QMatrix.GetNumberOfColumns(); ++c)
				if (m_QMatrix.Get(location, c) == maxOfRow)
					columnIndices.push_back(c);

			const uint32_t previousLocation{ location };

			location = columnIndices[rand() % columnIndices.size()];

			std::cout << location << "\t";

			// Colour final path to bright blue
			for (Transition* pTransition : *m_pTransitions)
			{
				if (pTransition->GetFromNode()->GetIndex() == previousLocation && pTransition->GetToNode()->GetIndex() == location)
				{
					pTransition->SetColour(MathUtils::RGBColour{ 0.f, 255.f, 255.f });
					break;
				}
			}
		}

		std::cout << std::endl;
		++m_CurrentIteration;
	}
}
```
