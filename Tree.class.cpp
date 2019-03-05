/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:39:44 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/04 15:38:59 by jfourne          ###   ########.fr       */
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
	return *this;
}

void					Tree::create_tree(std::vector<t_tok *> &tokens)
{
	std::vector<t_tok *>::iterator	it = tokens.begin();
	Tree				*left = new Tree;
	Tree				*right = new Tree;

	if (tokens.size() == 0)
		return ;
	this->_type = (*it)->type;
	this->_value = (*it)->value;
	free(*it);
	it = tokens.erase(tokens.begin());
	if (it == tokens.end()
		|| (this->_type == VAL || this->_type == NOT_VAL))
	{
		delete (left);
		delete (right);
		this->_left = NULL;
		this->_right = NULL;
		return ;
	}
	this->_left = left;
	left->create_tree(tokens);
	this->_right = right;
	right->create_tree(tokens);
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
