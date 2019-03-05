/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creator.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:44:53 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/05 10:25:22 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Creator.class.hpp"
#include "TreeBrowser.class.hpp"

Creator::Creator()
{
}

void			Creator::free_tree(Tree *tree)
{
	if (tree->_left)
		free_tree(tree->_left);
	if (tree->_right)
		free_tree(tree->_right);
	delete (tree);
}

Creator::~Creator()
{
	// std::vector<t_tok *>::iterator		it = this->_tokens.begin();
	std::multimap<char, Tree *>::iterator	itt = this->_rules.begin();

	this->_facts.clear();
	this->_queries.clear();
	this->_equal_rules.clear();
	// while (it != this->_tokens.end())
	// {
	// 	free(*it);
	// 	it++;
	// }
	this->_tokens.clear();
	while (itt != this->_rules.end())
	{
		free_tree(itt->second);
		itt++;
	}
	this->_rules.clear();
}

Creator::Creator(Creator const &src)
{
	*this = src;
}

Creator&				Creator::operator=(Creator const &rhs)
{
	this->_facts = rhs._facts;
	this->_queries = rhs._queries;
	this->_tokens = rhs._tokens;
	this->_equal_rules = rhs._equal_rules;
	// COPIER TOUS LES NEXT DES RULES
	this->_rules = rhs._rules;
	return (*this);
}

void					Creator::add_fact(char fact)
{
	std::vector<char>::iterator		it = this->_facts.begin();

	while (it != this->_facts.end())
	{
		if (*it == fact)
			return ;
		it++;
	}
	this->_facts.push_back(fact);
}

void					Creator::add_query(char query)
{
	this->_queries.push_back(query);
}

int						Creator::create_rule(char res, std::vector<t_tok *> &tokens)
{
	Tree				*new_rule = new Tree;

	new_rule->create_tree(tokens);
	std::cout << res << " = ";
	new_rule->print(0);
	this->_rules.insert(this->_rules.end(), std::pair<char, Tree *>(res, new_rule));
	return (EXIT_SUCCESS);
}

bool									Creator::check_rules(char &query)
{
	bool								ret = false;
	TreeBrowser							browser(this);
	std::multimap<char, Tree *>::iterator	itr = this->_rules.begin();

	while (itr != this->_rules.end())
	{
		if (itr->first == query)
			ret = browser.browse_tree(itr->second);
		if (ret == true)
			return (ret);
		itr++;
	}
	return (ret);
}

void					Creator::create_equal_rule(char res, char equal)
{
	this->_equal_rules.insert(this->_equal_rules.end(), std::pair<char, char>(res, equal));
}

char					Creator::check_equal_rule(char &query)
{
	std::multimap<char, char>::iterator		it = this->_equal_rules.begin();

	while (it != this->_equal_rules.end())
	{
		if (it->first == query)
			return (it->second);
		it++;
	}
	return (-1);
}

bool					Creator::check_all(char &query)
{
	char				equal;
	std::vector<char>::iterator it = this->_facts.begin();

	while (it != this->_facts.end())
	{
		if (query == *it)
			return (true);
		it++;
	}
	if ((equal = this->check_equal_rule(query)) != -1)
		return (check_all(equal));
	else
		return (this->check_rules(query));
}

void					Creator::execute(void)
{
	char				query;

	if (this->_queries.size() == 0)
		return ;
	query = *(this->_queries.begin());
	if (check_all(query) == true)
	{
		// CHECK ADD TO FACT ?
		// this->add_fact(query);
		std::cout << query << " : is true" << std::endl;
	}
	else
		std::cout << query << " : is false" << std::endl;
	this->_queries.erase(this->_queries.begin());
	this->execute();
}