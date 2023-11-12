#include "Node.h"
#include <iomanip>
#include <exception>

template <typename T>
class BinaryTree
{
private:
	std::shared_ptr<Node<T>> root_;
	int cntr_ = 0;
	size_t size_ = 0;

public:
	BinaryTree() : root_(nullptr) {}

	void insert(const T& value)
	{
		if (!root_)
		{
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
		std::cout << "\n";
		print_order_chatGPT(root_);
		std::cout << "\n";

	}

	bool find(const T& value)
	{
		std::shared_ptr<Node<T>> test = find_(value, root_);
		std::cout << "\n";
		if (test == nullptr)
		{
			std::cout << "none\n";
			return false;
		}

		return true;
	}

	bool erase(const T& value)
	{
		std::cout << "\n" << value << "\n";
		return erase_(value);
	}

private:

	bool erase_(const T& value)
	{
		std::shared_ptr<Node<T>> erased = find_(value, root_);
		if (!erased)
		{
			return false;
		}

		if (erased->left == nullptr && erased->right == nullptr)
		{
			std::shared_ptr<Node<T>> erased_parent = erased->parent.lock();
			if (!erased_parent)
			{
				erased.reset();
				root_.reset();
				return true;
			}
			if (erased_parent->left == erased)
			{
				erased_parent->left = nullptr;
				return true;
			}
			if (erased_parent->right == erased)
			{
				erased_parent->right = nullptr;
				return true;
			}
			throw std::logic_error("Error deleting resource");
		}
		if (erased->left != nullptr && erased->right == nullptr)
		{
			std::shared_ptr<Node<T>> erased_parent = erased->parent.lock();
			if (!erased_parent)
			{
				std::shared_ptr<Node<T>> new_root = erased->left;
				root_->left = nullptr;
				root_ = new_root;
				erased.reset();
				return true;
			}

			//std::cout << "\nerased->left != nullptr && erased->right == nullptr\n";

			std::shared_ptr<Node<T>> erased_chaild = erased->left;
			if (erased_parent->left == erased)
			{
				erased_parent->left = erased_chaild;
				erased_chaild->parent = erased_parent;
				erased->left = nullptr;
				erased = nullptr;
				return true;
			}
			if (erased_parent->right == erased)
			{
				erased_parent->right = erased_chaild;
				erased_chaild->parent = erased_parent;
				erased->right = nullptr;
				erased = nullptr;
				return true;
			}
			throw std::logic_error("Error deleting resource");
		}
		if (erased->left == nullptr && erased->right != nullptr)
		{
			std::shared_ptr<Node<T>> erased_parent = erased->parent.lock();
			if (!erased_parent)
			{
				std::shared_ptr<Node<T>> new_root = erased->right;
				root_->right = nullptr;
				root_ = new_root;
				erased.reset();
				return true;
			}

			//std::cout << "\nerased->left == nullptr && erased->right != nullptr\n";

			std::shared_ptr<Node<T>> erased_chaild = erased->right;
			if (erased_parent->left == erased)
			{
				erased_parent->left = erased_chaild;
				erased_chaild->parent = erased_parent;
				erased->left = nullptr;
				erased = nullptr;
				return true;
			}
			if (erased_parent->right == erased)
			{
				erased_parent->right = erased_chaild;
				erased_chaild->parent = erased_parent;
				erased->right = nullptr;
				erased = nullptr;
				return true;
			}
			throw std::logic_error("Error deleting resource");
		}

		if (erased->left != nullptr && erased->right != nullptr)
		{
			std::shared_ptr<Node<T>> erased_parent = erased->parent.lock();



			std::shared_ptr<Node<T>> erased_chaild_L = erased->left;
			std::shared_ptr<Node<T>> erased_chaild_R = erased->right;


			//std::cout << "\nerased->left != nullptr && erased->right != nullptr\n";

			std::shared_ptr<Node<T>> max = erased->left;

			if (max->right)
				while (max->right)
				{
					max = max->right;
				}

			if (!erased_parent)
			{
				if (max->left == nullptr)
				{
					max->parent.lock()->right = max->left;

					max->left = erased_chaild_L;
					max->right = erased_chaild_R;
					erased_chaild_L->parent = max;
					erased_chaild_R->parent = max;

					//max->right = erased->right;
					//max->parent = nullptr;
					//erased_chaild_R->parent = max;

					root_->left = nullptr;
					root_->right = nullptr;
					max->parent = root_->parent;
					root_ = max;
					return true;
				}
				if (max->left != nullptr)
				{
					//throw std::logic_error("Who are you? Where I am?");
					max->parent.lock()->right = max->right;
					max->parent.lock()->left = max->left;
					max->left = erased_chaild_L;
					max->right = erased_chaild_R;
					erased_chaild_L->parent = max;
					erased_chaild_R->parent = max;
					root_->left = nullptr;
					root_->right = nullptr;
					max->parent = root_->parent;
					root_ = max;
					return true;
				}
			}

			if (erased_parent->left == erased)
			{

				if (max->left == nullptr)
				{
					max->parent.lock()->right = max->left;
					erased_chaild_R->parent = max;
					erased_chaild_L->parent = max;
					max->parent = erased_parent;
					erased_parent->left = max;
					max->right = erased_chaild_R;
					max->left = erased_chaild_L;
					return true;
				}
				if (max->left != nullptr)
				{
					max->parent.lock()->right = max->right;
					erased_chaild_R->parent = max;
					max->parent = erased_parent;
					erased_parent->left = max;
					max->right = erased_chaild_R;
					return true;
				}
			}

			if (erased_parent->right == erased)
			{
				if (max->left == nullptr)
				{

					if (max != erased_chaild_L)
					{

						max->left = erased_chaild_L;
						erased_chaild_L->parent = max;
						max->left->right = nullptr;
					}
					max->parent = erased_parent;
					erased_parent->right = max;

					erased_chaild_R->parent = max;
					max->right = erased_chaild_R;
					return true;
				}
				if (max->left != nullptr)
				{
					max->parent.lock()->right = max->left;
					erased_parent->right = max;
					max->right = erased_chaild_R;

					return true;
				}
			}


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

	static void insertR(std::shared_ptr<Node<T>> currentN, const T& value)
	{
		if (value < currentN->data)
		{
			if (currentN->left)
			{
				insertR(currentN->left, value);
			}
			else
			{
				std::weak_ptr<Node<T>> weakPtr = currentN;
				currentN->left = std::make_shared<Node<T>>(value, weakPtr);
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
				std::weak_ptr<Node<T>> weakPtr = currentN;
				currentN->right = std::make_shared<Node<T>>(value, weakPtr);
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

