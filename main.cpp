
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <cassert>
#include "BinaryTree.h"

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
		// Создаем бинарное дерево
		BinaryTree<int> tree;
		tree.insert(5);
		tree.insert(3);
		tree.insert(7);
		tree.insert(2);
		tree.insert(4);
		tree.insert(6);
		tree.insert(8);
		tree.insert(4);
		tree.insert(0);
		tree.insert(2);
		tree.insert(-1);
		tree.insert(5);
		tree.insert(6);
		tree.insert(10);
		tree.insert(8);
		tree.insert(7);
		tree.insert(9);
		tree.insert(11);
		tree.print_in_order();
		tree.find(0);
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
