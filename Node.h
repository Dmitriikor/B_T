#pragma once

#include <utility>

template <typename T>
struct Node
{
	T data;

	std::shared_ptr	<Node<T>> left;
	std::shared_ptr	<Node<T>> right;
	std::weak_ptr	<Node<T>> parent;



	Node(const T& value) : data(value)/*, prev(this)*/
	{

	}

	Node(const T& value, std::weak_ptr<Node<T>> parent) : data(value), parent(parent)/*, parent(this)*/
	{

	}

	~Node()
	{

	}
};