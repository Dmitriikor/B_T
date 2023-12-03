
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <ctime> 
#include "BinaryTree.h"

void fill_randomly(BinaryTree<int>& root, std::vector<int>& random, int size = 10)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(-50, 50);

	for (int i = 0; i < size; ++i)
	{
		int random_value = dis(gen);
		random.push_back(random_value);
		root.insert(random_value);
	}
}

int return_randomly(std::vector<int>& random)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(0, (int)random.size() - (1));

	return random[dis(gen)];
}

int min(std::vector<int>& random)
{
	auto min = std::min_element(random.begin(), random.end());
	return *min;
}
int max(std::vector<int>& random)
{
	auto max = std::max_element(random.begin(), random.end());
	return *max;
}

int main()
{
	{
		//BinaryTree<int> tree;
		//tree.print();
		//std::cout << "\n\n\n";
		//tree.print_in_order();
		//std::cout << " \n size: " << tree.size();
		//std::cout << " \n";
		////tree.find(1);
	}
	{
		while (true)
		{
			std::vector<int> random;
			std::vector<int> random2;
			BinaryTree<int> tree;
			fill_randomly(tree, random);
			tree.print_in_order();

			//std::cout <<"\n"<< min(random) << " / "	<< tree.min() << "\n";
			assert(min(random) == tree.min());

			assert(max(random) == tree.max());
			if (tree.erase(return_randomly(random)))
			{
				tree.to_vector(random2);
				std::cout <<"\n"<< random.size() << " / "	<< random2.size() << "\n";
				assert(random.size()-1 == random2.size());


				tree.print_in_order();
				tree.print();
				std::cout << "\n";
				for (auto it = tree.begin(); it != tree.end(); ++it)
				{
					std::cout << "\\"<< *it ;
				}
				// std::cout << "\n";
				// for (auto it = tree.begin(); it != tree.end(); --it)
				// {
				// 	std::cout << "/"<< *it ;
				// }
				std::cout << "\n";
				system("pause");
				
				system("cls");
				BinaryTree<int> treeLRT;
				treeLRT.insert(1);
				treeLRT.insert(2);
				treeLRT.insert(3);
				treeLRT.print_in_order();
				std::cout << "\n";
				treeLRT.left_rotate(2);
				treeLRT.print_in_order();

std::cout << "\n";
std::cout << "\n";

				BinaryTree<int> treeRRT;
				treeRRT.insert(3);
				treeRRT.insert(2);
				treeRRT.insert(1);
				treeRRT.print_in_order();
				std::cout << "\n";
				treeRRT.right_rotate(2);
				treeRRT.print_in_order();

				std::cout << "\n";
				system("pause");

				std::cout << "\n";
				tree.print_in_order();

				tree.check();

				std::cout << "\n" << random2[5] << "\n";
				tree.left_rotate(random2[5]);
				tree.print_in_order();

				std::cout << "\n" << random2[7] << "\n";
				tree.right_rotate(random2[7]);
				tree.print_in_order();


				system("pause");
			}
			else
			{
				return -1;
			}
		}


		//BinaryTree<int> tree;

		//tree.insert(13);
		//tree.insert(45);
		//tree.insert(-29);
		//tree.insert(46);
		//tree.insert(19);
		//tree.insert(-14);
		//tree.insert(-31);
		//tree.insert(34);
		//tree.insert(18);
		//tree.insert(32);

		//tree.print_in_order();
		//tree.erase(13);
		//tree.print_in_order();



		//tree.find(8);
		//tree.find(9);
		//tree.find(7);
		//tree.find(5);
		//tree.find(0);
		//tree.find(-1);

		//tree.find(11);

		//tree.find(29);
		//tree.find(28);
		//tree.find(30);
		//tree.find(35);
		//tree.find(20);
		//tree.find(17);
		//tree.find(12);


		//tree.find(10);
		//tree.find(19);

		//// Проверяем поиск
		//std::shared_ptr<Node<int>> foundNode;
		//foundNode = tree.find(5);
		//assert(foundNode != nullptr);
		//assert(foundNode->data == 5);
		//foundNode = tree.find(3);
		//assert(foundNode != nullptr);
		//assert(foundNode->data == 3);
		//foundNode = tree.find(8);
		//assert(foundNode != nullptr);
		//assert(foundNode->data == 8);
		//foundNode = tree.find(1);
		//assert(foundNode == nullptr);
		//foundNode = tree.find(9);
		//assert(foundNode == nullptr);
		//std::cout << "All tests passed." << std::endl;

	}
	_CrtDumpMemoryLeaks();
	return 0;
}
