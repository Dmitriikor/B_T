#include "Node.h"
#include <iomanip>
#include <exception>

template <typename T>
class BinaryTree
{
private:
	std::shared_ptr<Node<T>> root_;
	//int cntr_ = 0;
	size_t size_ = 0;

public:
	BinaryTree() : root_(nullptr) {}

	void insert(const T& value)
	{
		if (!root_) {
			root_ = std::make_shared<Node<T>>(value);
		}
		else {
			insertR(root_, value);
		}
		++size_;
	}

	size_t size()
	{
		return size_;
	}

	void print()
	{
		print(root_);
	}

	void print_in_order()
	{
		//print_orderR(root_, cntr_);
		//std::cout << "\n";
		print_order_chatGPT(root_);
		std::cout << "\n";

	}

	bool find(const T& value)
	{
		std::shared_ptr<Node<T>> test = find_(value, root_);
		std::cout << "\n";
		//if (test == nullptr)
		//{
		//	std::cout << "none\n";
		//	return false;
		//}
		erase(value);
		print_in_order();
		system("pause");






		return true;
	}

private:

	void erase(const T& value)
	{
		std::shared_ptr<Node<T>> erased = find_(value, root_);
		if (!erased)
		{
			return;
		}

		if (erased->left == nullptr && erased->right == nullptr)
		{
			std::shared_ptr<Node<T>> parent = erased->parent.lock();
			if (!parent)
			{
				return;
			}
			if (parent->left == erased)
			{
				parent->left = nullptr;
				return;
			}
			if (parent->right == erased)
			{
				parent->right = nullptr;
				return;
			}
			throw std::logic_error("Error deleting resource");
		}
		if (erased->left != nullptr && erased->right == nullptr)
		{
			std::shared_ptr<Node<T>> parent = erased->parent.lock();
			if (!parent)
			{
				return;
			}

			std::cout << "\nerased->left != nullptr && erased->right == nullptr\n";

			std::shared_ptr<Node<T>> erased_chaild = erased->left;
			if (parent->left == erased)
			{
				parent->left = erased_chaild;
				erased_chaild->parent = parent;
				erased->left = nullptr;
				erased = nullptr;
				return;
			}
			if (parent->right == erased)
			{
				parent->right = erased_chaild;
				erased_chaild->parent = parent;
				erased->right = nullptr;
				erased = nullptr;
				return;
			}
			throw std::logic_error("Error deleting resource");
		}
		if (erased->left == nullptr && erased->right != nullptr)
		{
			std::shared_ptr<Node<T>> parent = erased->parent.lock();
			if (!parent)
			{
				return;
			}

			std::cout << "\nerased->left == nullptr && erased->right != nullptr\n";

			std::shared_ptr<Node<T>> erased_chaild = erased->left;
			if (parent->left == erased)
			{
				parent->left = erased_chaild;
				erased_chaild->parent = parent;
				erased->left = nullptr;
				erased = nullptr;
				return;
			}
			if (parent->right == erased)
			{
				parent->right = erased_chaild;
				erased_chaild->parent = parent;
				erased->right = nullptr;
				erased = nullptr;
				return;
			}
			throw std::logic_error("Error deleting resource");
		}



		if (erased->left != nullptr && erased->right != nullptr)
		{


		}

	}

	std::shared_ptr<Node<T>> find_(T val, std::shared_ptr<Node<T>> currentN)
	{
		while (currentN)
		{
			if (currentN->data == val)
			{
				return currentN;
			}
			if (currentN->data > val)
			{
				currentN = currentN->left;
			}
			if (currentN == nullptr)
				break;
			if (currentN->data == val)
			{
				return currentN;
			}
			if (currentN->data < val)
			{
				currentN = currentN->right;
			}
		}
		return nullptr;
	}

	//if (currentN)
	//{
	//	std::cout << currentN->data;
	//	if (currentN->data >= val)
	//	{
	//		if (currentN->left == nullptr)
	//			return currentN;

	//		findR(currentN->left, val);
	//	}
	//	if (currentN->data < val)
	//	{
	//		if (currentN->right == nullptr /*&& val > currentN->data*/)
	//			return currentN;
	//		findR(currentN->right, val);

	//	}
	//}

//}



	static void print_orderR(std::shared_ptr<Node<T>> currentN, int counter)
	{
		if (currentN)
		{
			print_orderR(currentN->right, counter + 1);

			for (size_t i = 0; i < counter; i++)
			{
				std::cout << " \t";
			}
			std::cout << currentN->data << "\n";

			print_orderR(currentN->left, counter + 1);
		}
	}


	void print(std::shared_ptr<Node<T>> currentN)
	{
		if (currentN)
		{
			print(currentN->left);
			std::cout << currentN->data << " ";
			print(currentN->right);
		}
	}

	void insertR(std::shared_ptr<Node<T>> currentN, const T& value)
	{
		if (value < currentN->data)
		{
			if (currentN->left)
			{
				insertR(currentN->left, value);
			}
			else
			{
				currentN->left = std::make_shared<Node<T>>(value);
				currentN->left->parent = currentN;
			}
		}
		else
		{
			if (currentN->right)
			{
				insertR(currentN->right, value);
			}
			else
			{
				currentN->right = std::make_shared<Node<T>>(value);
				currentN->right->parent = currentN;
			}
		}
	}
};

template <typename T>
void print_order_chatGPT(std::shared_ptr<Node<T>> const currentN, int level = 0)
{
	if (currentN)
	{
		print_order_chatGPT(currentN->right, level + 1);

		for (int i = 0; i < level; ++i)
		{
			std::cout << "|\t";
		}

		std::cout << currentN->data << "\n";

		print_order_chatGPT(currentN->left, level + 1);
	}

}

