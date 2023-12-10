#include "Node.h"
#include <iomanip>
#include <exception>
#include <iterator> 
#include <algorithm>

template <typename U>
class no_L_�hildren
{
public:
	bool operator()(const std::shared_ptr<Node<U>> node) const
	{
		return (node->left == nullptr);
	}
};

template <typename U>
class no_R_�hildren
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

	//int left_height = 0;
	//int right_height = 0;

	friend class iterator;
public:
	BinaryTree() : root_(nullptr) {}


	void insert(const T& value)
	{
		std::shared_ptr<Node<T>> currentN;

		if (!root_)
		{
			root_ = std::make_shared<Node<T>>(value);
			//currentN = root_;
			++size_;
			return;
		}
		else 
		{
			//std::cout << "\n" << "print before insert\n";
			//print_order_chatGPT(root_);
			currentN = insertR(root_, value);
			//recalculate_levels__(currentN);
			++size_;
			std::cout << "\n" << "print after insert\n";
			print_order_chatGPT(root_);
			check_lvl_(currentN);
			std::cout << "\n" ;
			std::cout << "\n" << "print after check_lvl_\n";
			print_order_chatGPT(root_);
			return;
		}
		
		throw 1;
	}

	void check_lvl_(std::shared_ptr<Node<T>> currentN)
	{
		if (!currentN)
		{
			return;
		}
		//currentN = currentN->parent.lock();

/*
		int L_temp = 0;
		int R_temp = 0;

		if(currentN->left == nullptr)
		{
			L_temp = 0;
		}
		else
		{
			L_temp = currentN->left->height;
		}

		if(currentN->right == nullptr)
		{
			R_temp = 0;
		}
		else
		{
			R_temp = currentN->right->height;
		}
		*/

			int L_temp = (currentN->left == nullptr) ? 0 : (currentN->left->height);
			int R_temp = (currentN->right == nullptr) ? 0 : (currentN->right->height);
		
		if (L_temp - R_temp > 1)
		{
			std::cout <<"\n" << currentN->data << " = L_temp - R_temp > 1 Check\n";
			print_order_chatGPT(root_);
			//
			//if(currentN->left->left == nullptr)
			//	check_lvl_();
			//
			right_rotate_(currentN);


			std::cout <<"\n";
			std::cout <<"\n" << currentN->data << "Check after right rotate\n";
			print_order_chatGPT(root_);

		}
		else if (L_temp - R_temp < -1)
		{
			std::cout <<"\n"  << currentN->data << " = L_temp - R_temp < -1 Check\n";
			print_order_chatGPT(root_);
			//
			//if(currentN->right->right == nullptr)
			//	right_rotate_(currentN->right);
			//
			left_rotate_(currentN);

			std::cout <<"\n";
			std::cout <<"\n" << currentN->data << "Check after left rotate\n";
			print_order_chatGPT(root_);
		}

		recalculate_levels__(currentN);
		std::shared_ptr<Node<T>> parentN = currentN->parent.lock();
		check_lvl_(parentN);
	}

	size_t size()
	{
		return size_;
	}

	void print()
	{
		print_(root_);
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
		if (!root_)
			throw std::runtime_error("Root is nullptr");

		return min_(root_)->data;

		//std::shared_ptr<Node<T>> result = min_(root_);

		//if (!result)
		//	return NULL; // trow

		//return result->data;
	}

	T max()
	{
		if (!root_)
			throw std::runtime_error("Root is nullptr");

		return max_(root_)->data;
	}

	void to_vector(std::vector<T>& accum)
	{
		to_vector_(accum, root_);
	}

private:
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	private:
		std::shared_ptr<Node<T>> currentN;
		friend class BinaryTree;
		bool is_first_m = true;
		bool is_first_l = true;
	public:
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::forward_iterator_tag;

		explicit iterator(std::shared_ptr<Node<T>> currentN) : currentN(currentN)
		{
		}

		reference operator*()
		{
			return currentN->data;
		}

		iterator& operator++()
		{
			if (currentN == nullptr)
				throw std::runtime_error("currentN is nullptr");

			if (currentN->right != nullptr)
			{
				currentN = min_(currentN->right);
			}
			else
			{
				while (currentN->parent.lock() != nullptr && currentN->parent.lock()->right == currentN)
				{
					currentN = currentN->parent.lock();
				}
				currentN = currentN->parent.lock();
			}

			return *this;
		}

		iterator& operator--()
		{
			if (currentN == nullptr)
				throw std::runtime_error("currentN is nullptr");

			if (currentN->left != nullptr)
			{
				currentN = currentN->left;
			}
			else
			{
				currentN = currentN->parent.lock()->right;
			}

			return *this;
		}

		bool operator!=(const iterator& other) const
		{
			return currentN != other.currentN;
		}

	};

	bool erase_(const T& value)
	{
		std::shared_ptr<Node<T>> erased = find_(value, root_);

		if (!erased)
			return false;

		--size_;

		return erase__(erased);
	}

	bool erase__(std::shared_ptr<Node<T>> erased)
	{
		std::shared_ptr<Node<T>> parentN = erased->parent.lock();

		if (erased->left == nullptr && erased->right == nullptr)
			erase_no_child(erased, root_);
		else if (erased->left != nullptr && erased->right == nullptr)
			erase_L_child(erased, root_);
		else if (erased->left == nullptr && erased->right != nullptr)
			erase_R_child(erased, root_);
		else
		{
			//������� ������������ � ����� ���������
			std::shared_ptr<Node<T>> max = max_(erased->left);

			parentN = max->parent.lock();

			if (parentN == erased)
				parentN = max;

			erase_L_and_R_child(erased, root_, max);
		}

		recalculate_levels_(parentN);

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
	//		if (currentN->right == nullptr //&& val > currentN->data*/)
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


	void print_(std::shared_ptr<Node<T>> currentN)
	{
		if (currentN)
		{
			print_(currentN->left);
			std::cout << currentN->data << "\\";
			print_(currentN->right);
		}
	}


	static std::shared_ptr<Node<T>> insertR(std::shared_ptr<Node<T>> currentN, const T& value)
	{
		if (value < currentN->data)
		{
			if (currentN->left)
			{
				return insertR(currentN->left, value);
			}
			else
			{
				std::weak_ptr<Node<T>> weakPtr = currentN;
				currentN->left = std::make_shared<Node<T>>(value, weakPtr);
				return currentN->left;
			}
		}
		else
		{
			if (currentN->right)
			{
				return insertR(currentN->right, value);
			}
			else
			{
				std::weak_ptr<Node<T>> weakPtr = currentN;
				currentN->right = std::make_shared<Node<T>>(value, weakPtr);
				return currentN->right;
			}
		}

		throw 1;
	}
public:
	void right_rotate(const T& value)
	{
		right_rotate_(find_(value, root_));
	}
	void left_rotate(const T& value)
	{
		left_rotate_(find_(value, root_));
	}
	void check()
	{
		check__(root_);
	}

	void check__(std::shared_ptr<Node<T>> currentN)
	{
		if (currentN)
		{
			check__(currentN->left);

			if (currentN != root_ && currentN->parent.lock() == nullptr)
				std::cout << currentN->data << "\\\a";

			check__(currentN->right);
		}
	}

	int height_of_binary_tree()
	{
		int test = height_of_binary_tree_(root_);
		//min__(root_, left_height);
		//max__(root_, right_height);
		//int max = std::max(left_height, right_height);
		//assert(test == max+1);

		return test;
	}

private:
	void recalculate_levels__(std::shared_ptr<Node<T>> currentN)
	{
		if (currentN == nullptr)
		{
			//throw 1;
			return;
		}
			size_t left_height = (currentN->left == nullptr) ? 0 : (currentN->left->height);
			size_t right_height = (currentN->right == nullptr) ? 0 : (currentN->right->height);

			currentN->height = std::max(left_height, right_height) + 1;
	}


	void recalculate_levels_(std::shared_ptr<Node<T>> currentN)
	{
		if (currentN == nullptr)
		{
			//throw 1;
			return;
		}

		while (currentN != nullptr)
		{
			size_t left_height = (currentN->left == nullptr) ? 0 : (currentN->left->height);
			size_t right_height = (currentN->right == nullptr) ? 0 : (currentN->right->height);

			currentN->height = std::max(left_height, right_height) + 1;
			currentN = currentN->parent.lock();
		}
	}

	static size_t height_of_binary_tree_(std::shared_ptr<Node<T>> currentN)
	{
		if (currentN == nullptr)
			return 0;

		return currentN->height;
		/*if (!currentN)
		{
			return 0;
		}

		size_t left_height = height_of_binary_tree_(currentN->left);
		size_t right_height = height_of_binary_tree_(currentN->right);
		return std::max(left_height, right_height) + 1;*/
	}

	/*
		x (currentN)
		 \
		  y			=>			y
		   \				   / \
			z				  x   z
	
	*/
	void left_rotate_(std::shared_ptr<Node<T>> x)
	{
		if (x->right == nullptr)
		{
			return;
			//throw 1;
		}

		if (x->right->right == nullptr)
		{
			return;
			//throw 1;
		}
		/*
		bool is_temp_used = false;
		std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(-1);
		if (x->right->right == nullptr)
		{
			x->right->right = temp;
			temp->parent.lock() = x->right;
			is_temp_used = true;
		}*/

		std::shared_ptr<Node<T>> y = x->right;

		x->right = y->left;
		if (y->left != nullptr)
		{
			y->left->parent.lock() = x;
		}

		y->parent.lock() = x->parent.lock();
		if (x->parent.lock() == nullptr)
		{
			root_ = y;
		}
		else
		{
			if (x == x->parent.lock()->left) //left
			{
				x->parent.lock()->left = y;
			}
			else
			{
				x->parent.lock()->right = y;
			}
		}

		y->left = x;
		x->parent.lock() = y;
/*
		if(is_temp_used)
			erase__(temp);
			*/
	}


/*
				x (currentN)
			  /
		  	y					=>   y
		  /				  			/ \
		z				  		   x   z
	
	*/
	void right_rotate_(std::shared_ptr<Node<T>> x)
	{
		if (x->left == nullptr)
		{
			return;
			
			//throw 1;
		}

		if (x->left->left == nullptr)		
		{
			return;
			
			//throw 1;
		}
/*
		bool is_temp_used = false;
		std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(-1);
		if (x->left->left == nullptr)
		{
			x->left->left = temp;
			temp->parent.lock() = x->left;
			is_temp_used = true;
		}
*/

		std::shared_ptr<Node<T>> y = x->left;

		x->left = y->right;
		if (y->right != nullptr)
		{
			y->right->parent.lock() = x;
		}

		y->parent = x->parent;
		if (x->parent.lock() == nullptr)
		{
			root_ = y;
		}
		else
		{
			if (x == x->parent.lock()->left)
			{
				x->parent.lock()->left = y;
			}
			else
			{
				x->parent.lock()->right = y;
			}
		}

		y->right = x;
		x->parent.lock() = y;

/*
		if(is_temp_used)
			erase__(temp);
			*/
	}

public:
	iterator begin()
	{
		return iterator(min_(root_));
	}

	iterator end()
	{
		return iterator(nullptr);
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

		std::cout << currentN->data << "(" << currentN->height << ")" << "\n";

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
void erase_L_and_R_child(std::shared_ptr<Node<T>> erased, std::shared_ptr<Node<T>>& root_, std::shared_ptr<Node<T>> max)
{
	std::shared_ptr<Node<T>> erased_parent = erased->parent.lock();
	std::shared_ptr<Node<T>> erased_child_L = erased->left;
	std::shared_ptr<Node<T>> erased_child_R = erased->right;

	//std::cout << "\nerased->left != nullptr && erased->right != nullptr\n";

	if (!max)
		throw std::logic_error("Error deleting resource");

	//���� ��������� � ���������� �� ������� ���������� "��������-����� ������"
	if (max != erased_child_L)
	{
		//��������� ������ ����� max � ��� ���������
		max->parent.lock()->right = max->left;

		if (max->left != nullptr)
			max->left->parent = max->parent;

		//��������� max � ��� ������ ������ ������:
		erased_child_L->parent = max;
		max->left = erased_child_L;
	}

	//��������� max � ��� ������ ������� ������:
	erased_child_R->parent = max;
	max->right = erased_child_R;

	//���������� max �� ������ ��������
	max->parent = erased_parent; //?? error

	//���� �������� ����, �� ���������� ��� �� max
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
std::shared_ptr<Node<T>> min_(std::shared_ptr<Node<T>> currentN)
{
	if (!currentN)
		return nullptr;

	while (currentN->left)
	{
		currentN = currentN->left;
	}

	return currentN;
}

template <typename T>
std::shared_ptr<Node<T>> max_(std::shared_ptr<Node<T>> currentN)
{
	if (!currentN)
		return nullptr;

	while (currentN->right)
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
//template <typename T>
