/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:39:44 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/07 11:08:15 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tree.class.hpp"

Tree::Tree()
{
}

Tree::~Tree()
{
}

Tree::Tree(Tree const &src)
{
	*this = src;
}

Tree&					Tree::operator=(Tree const &rhs)
{
	this->_left = rhs._left;
	this->_right = rhs._right;
	this->_type = rhs._type;
	this->_value = rhs._value;
	return *this;
}

void					Tree::create_tree(std::vector<t_tok *> &tokens,
									std::vector<t_tok *>::iterator &it)
{
	Tree				*left = new Tree;
	Tree				*right = new Tree;

	this->_type = (*it)->type;
	this->_value = (*it)->value;
	if (it + 1 == tokens.end()
		|| (this->_type == VAL || this->_type == NOT_VAL))
	{
		delete (left);
		delete (right);
		this->_left = NULL;
		this->_right = NULL;
		return ;
	}
	this->_left = left;
	it++;
	left->create_tree(tokens, it);
	it++;
	this->_right = right;
	right->create_tree(tokens, it);
}

void				Tree::print(int i)
{
	int				j = 0;

	std::cout << this->_value << std::endl;
	while (j < i)
	{
		std::cout << "  ";
		j++;
	}
	std::cout << "Left : ";
	if (this->_left)
		this->_left->print(i + 1);
	j = 0;
	while (j < i)
	{
		std::cout << "  ";
		j++;
	}
	std::cout << "Right : ";
	if (this->_right)
		this->_right->print(i + 1);
	std::cout << std::endl;
}
