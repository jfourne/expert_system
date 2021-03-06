/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeBrowser.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:28:37 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/20 10:21:21 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TreeBrowser.class.hpp"

TreeBrowser::TreeBrowser(Creator *creator): _creator(creator)
{
}

TreeBrowser::TreeBrowser(TreeBrowser const &src)
{
	*this = src;
}

TreeBrowser::~TreeBrowser()
{
}

TreeBrowser&			TreeBrowser::operator=(TreeBrowser const &rhs)
{
	this->_creator = rhs._creator;
	return (*this);
}

bool			check_and(bool left, bool right)
{
	if (left && right)
		return (true);
	return (false);
}

bool			check_or(bool left, bool right)
{
	if (left || right)
		return (true);
	return (false);
}

bool			check_xor(bool left, bool right)
{
	bool		ret = false;

	if (left && !right)
		ret = true;
	else if (right && !left)
		ret = true;
	else
		ret = false;
	return (ret);
}

bool			check_val(Creator *creator, char value)
{
	return (creator->check_all(value));
}

bool			check_not_val(Creator *creator, char value)
{
	return (!(creator->check_all(value)));
}

bool			TreeBrowser::check_conditions(bool left, bool right, Tree *tree)
{
	bool		ret = false;
	static bool		(*ptr_func[])(bool, bool) = {
		&check_and,
		&check_or,
		&check_xor,
	};

	if (tree->_type < VAL)
	{
		ret = ptr_func[tree->_type](left, right);
		std::cout << "  With operator : '" << tree->_value << "'"
		<< " left is " << (left ? "true" : "false")
		<< ", right is " << (right ? "true" : "false") 
		<< " so the result is " << (ret ? "true" : "false") << std::endl;
		return (ret);
	}
	else if (tree->_type == VAL)
		return (check_val(this->_creator, tree->_value));
	else if (tree->_type == NOT_VAL)
		return (check_not_val(this->_creator, tree->_value));
	else
		return (false);
}

bool			TreeBrowser::browse_tree(Tree *tree)
{
	bool		left = false;
	bool		right = false;

	if (tree->_left)
		left = this->browse_tree(tree->_left);
	if (tree->_right)
		right = this->browse_tree(tree->_right);
	return (this->check_conditions(left, right, tree));
}