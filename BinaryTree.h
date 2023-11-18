#include "Node.h"
#include <iomanip>
#include <exception>


template <typename U>
class no_L_сhildren
{
public:
    bool operator()(const std::shared_ptr<Node<U>> node) const 
	{
        return (node->left == nullptr);
    }
};

template <typename U>
class no_R_сhildren
{
public:
    bool operator()(const std::shared_ptr<Node<U>> node) const 
	{
        return (node->right == nullptr);
    }
};

template <typename T>
class BinaryTree
{
private:
	std::shared_ptr<Node<T>> root_;
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
		//print_orderR(root_, 0);
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

	T min()
	{
		if(!root_)
			return NULL; // trow

		return min_(root_)->data;
	}
	T max()
	{
		if(!root_)
			return NULL; // trow

		return max_(root_)->data;
	}


	void to_vector(std::vector<T>& accum)
	{
		to_vector_(accum, root_);
	}
	




private:

	bool erase_(const T& value)
	{
		std::shared_ptr<Node<T>> erased = find_(value, root_);

		if (!erased)
			return false;

		--size_;

		if (erased->left == nullptr && erased->right == nullptr)
			erase_no_child(erased, root_);
		else if (erased->left != nullptr && erased->right == nullptr)
			erase_L_child(erased, root_);
		else if (erased->left == nullptr && erased->right != nullptr)
			erase_R_child(erased, root_);
		else
		//if (erased->left != nullptr && erased->right != nullptr)
		erase_L_and_R_child(erased, root_);

		return true;
	}

	std::shared_ptr<Node<T>> find_(const T& val, std::shared_ptr<Node<T>> currentN)
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
				continue;
			}

			//if (currentN->data < val)
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

template <typename T>
	void erase_no_child(std::shared_ptr<Node<T>>& erased, std::shared_ptr<Node<T>>& root_)
	{
		std::shared_ptr<Node<T>> erased_parent = erased->parent.lock();

		if (!erased_parent)
		{
			//erased.reset();
			root_.reset();
			return;
		}

		if (erased_parent->left == erased)
		{
			erased_parent->left = nullptr;
			return;
		}

		if (erased_parent->right == erased)
		{
			erased_parent->right = nullptr;
			return;
		}

		throw std::logic_error("Error deleting resource");
	}
template <typename T>
	bool erase_L_child(std::shared_ptr<Node<T>>& erased, std::shared_ptr<Node<T>>& root_)
	{
		std::shared_ptr<Node<T>> parent = erased->parent.lock();
		std::shared_ptr<Node<T>> child = erased->left;

		if (!parent)
		{
			/*
			std::shared_ptr<Node<T>> new_root = erased->left;
			root_->left = nullptr;
			root_ = new_root;
			erased.reset();
			*/
			child->parent = root_->parent;
			root_ = child;
			return true;
		}

		//std::cout << "\nerased->left != nullptr && erased->right == nullptr\n";

		if (erased == parent->left)
		{
			parent->left = child;
			child->parent = parent;
			//erased->left = nullptr;
			//erased.reset(); //erased = nullptr;
			return true;
		}

		if (erased == parent->right)
		{
			parent->right = child;
			child->parent = parent;
			//erased->right = nullptr;
			//erased.reset();//erased = nullptr;
			return true;
		}

		throw std::logic_error("Error deleting resource");
	}
template <typename T>
	bool erase_R_child(std::shared_ptr<Node<T>>& erased, std::shared_ptr<Node<T>>& root_)
	{
		std::shared_ptr<Node<T>> parent = erased->parent.lock();
		std::shared_ptr<Node<T>> child = erased->right;

		if (!parent)
		{
			/*std::shared_ptr<Node<T>> new_root = erased->right;
			root_->right = nullptr;
			root_ = new_root;
			erased.reset();*/
			child->parent = root_->parent;
			root_ = child;
			return true;
		}

		//std::cout << "\nerased->left == nullptr && erased->right != nullptr\n";

		if (erased == parent->left)
		{
			parent->left = child;
			child->parent = parent;
			//erased->left = nullptr;
			//erased.reset(); //erased = nullptr;
			return true;
		}

		if (erased == parent->right)
		{
			parent->right = child;
			child->parent = parent;
			//erased->right = nullptr;
			//erased.reset(); //erased = nullptr;
			return true;
		}

		throw std::logic_error("Error deleting resource");

	}
template <typename T>
	void erase_L_and_R_child(std::shared_ptr<Node<T>>& erased, std::shared_ptr<Node<T>>& root_)
	{
		std::shared_ptr<Node<T>> erased_parent = erased->parent.lock();
		std::shared_ptr<Node<T>> erased_child_L = erased->left;
		std::shared_ptr<Node<T>> erased_child_R = erased->right;

		//std::cout << "\nerased->left != nullptr && erased->right != nullptr\n";

		std::shared_ptr<Node<T>> max = erased->left;

		while (max->right)
		{
			max = max->right;
		}

		if (!max)
			throw std::logic_error("Error deleting resource");

		//если удаляемый и заменяемый не связаны отношением "родитель-левый ребёнок"
		if (max != erased_child_L)
		{
			//разрываем старую связь max с его родителем
			max->parent.lock()->right = max->left;

			if (max->left != nullptr)
				max->left->parent = max->parent;

			//связываем max и его нового левого ребёнка:
			erased_child_L->parent = max;
			max->left = erased_child_L;
		}

		//связываем max и его нового правого ребёнка:
		erased_child_R->parent = max;
		max->right = erased_child_R;

		//направляем max на нового родителя
		max->parent = erased_parent; //?? error

		//если родитель есть, то направляем его на max
		if (erased_parent != nullptr)
		{
			if (erased == erased_parent->left)
				erased_parent->left = max;
			else
				erased_parent->right = max;
		}
		else
			root_ = max;
	}
	template <typename T>
	std::shared_ptr<Node<T>> min_ (std::shared_ptr<Node<T>> currentN)
	{
		if(!currentN)
			return nullptr;
		auto t_min = currentN->data;
		while(currentN->left)
		{
			currentN = currentN->left;
		}
		return currentN;

	}

	template <typename T>
	std::shared_ptr<Node<T>> max_ (std::shared_ptr<Node<T>> currentN)
	{
		if(!currentN)
			return nullptr;
	
		while(currentN->right)
		{
			currentN = currentN->right;
		}
		return currentN;

	}
	template <typename T>
	void to_vector_(std::vector<T>& accum, std::shared_ptr<Node<T>> currentN)
	{
		if (currentN)
		{
			to_vector_(accum, currentN->left);
			accum.push_back(currentN->data);
			to_vector_(accum, currentN->right);
		}
	}