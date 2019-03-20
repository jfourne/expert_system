/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creator.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:44:53 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/20 10:16:16 by jfourne          ###   ########.fr       */
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
	std::multimap<t_tok *, Tree *>::iterator	itt = this->_rules.begin();
	std::multimap<t_tok *, t_tok *>::iterator	ite = this->_equal_rules.begin();

	this->_facts.clear();
	this->_queries.clear();
	while (ite != this->_equal_rules.end())
	{
		if (ite->first)
			free(ite->first);
		if (ite->second)
			free(ite->second);
		ite++;
	}
	this->_equal_rules.clear();
	while (itt != this->_rules.end())
	{
		if (itt->first)
			free(itt->first);
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
	this->_equal_rules = rhs._equal_rules;
	this->_rules = rhs._rules;
	return (*this);
}

// Add fact to list and check if it doesn't already exist

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

// Add query to list

void					Creator::add_query(char query)
{
	this->_queries.push_back(query);
}

// Create rule from tokens

int						Creator::create_rule(t_tok *res, std::vector<t_tok *> &tokens)
{
	Tree							*new_rule = new Tree;
	std::vector<t_tok *>::iterator	it = tokens.begin();

	new_rule->create_tree(tokens, it);
	std::cout << res->value << " = ";
	new_rule->print(0);
	this->_rules.insert(this->_rules.end(), std::pair<t_tok *, Tree *>(res, new_rule));
	return (EXIT_SUCCESS);
}

// Check rule list in execution

bool									Creator::check_rules(char &query)
{
	bool								ret = false;
	TreeBrowser							browser(this);
	std::multimap<t_tok *, Tree *>::iterator	itr = this->_rules.begin();

	while (itr != this->_rules.end())
	{
		if (itr->first->value == query)
			ret = browser.browse_tree(itr->second);
		if (ret == true)
		{
			if (itr->first->type == VAL)
				return (ret);
			else
				return (false);
		}
		itr++;
	}
	return (ret);
}

// Create equality list

void					Creator::create_equal_rule(t_tok *res, char equal, bool valid)
{
	t_tok				*equality;

	if ((equality = (t_tok *) malloc(sizeof (t_tok))) == NULL)
		return ;
	equality->value = equal;
	if (valid == true)
	{
		equality->type = VAL;
		res->type == NOT_VAL ? std::cout << "not " : std::cout ;
		std::cout << res->value << " = " << equal << std::endl << std::endl;
	}
	else
	{
		equality->type = NOT_VAL;
		res->type == NOT_VAL ? std::cout << "not " : std::cout ;
		std::cout << res->value << " = not " << equal << std::endl << std::endl;
	}
	this->_equal_rules.insert(this->_equal_rules.end(), std::pair<t_tok *, t_tok *>(res, equality));
}

// Check equal list in execution

char					Creator::check_equal_rule(char &query)
{
	bool									ret = false;
	std::multimap<t_tok *, t_tok *>::iterator		it = this->_equal_rules.begin();

	while (it != this->_equal_rules.end())
	{
		if (it->first->value == query)
		{
			if ((it->second)->type == NOT_VAL && check_all((it->second)->value) == false)
			{
				std::cout << " " << query << " : is true because " << (it->second)->value << " is false" << std::endl;
				ret = true;
				if (it->first->type == NOT_VAL)
					ret = false;
				return (ret);
			}
			else if ((it->second)->type == VAL && check_all((it->second)->value) == true)
			{
				std::cout << " " << query << " : is true because " << (it->second)->value << " is true" << std::endl;
				ret = true;
				if (it->first->type == NOT_VAL)
					ret = false;
				return (ret);
			}
		}
		it++;
	}
	return (ret);
}

// Check all list of rules and fact to see if the query is true

bool					Creator::check_all(char &query)
{
	char				equal;
	bool				ret = false;
	std::vector<char>::iterator it = this->_facts.begin();

	while (it != this->_facts.end())
	{
		if (query == *it)
		{
			std::cout << " " << query << " : is true" << std::endl;
			return (true);
		}
		it++;
	}
	if ((equal = this->check_equal_rule(query)) == true)
	{
		this->add_fact(query);
		return (true);
	}
	else
	{
		ret = this->check_rules(query);
		if (ret == true)
		{
			this->add_fact(query);
			std::cout << " " << query << " : is true because the rule validate it" << std::endl;
		}
		else
			std::cout << " " << query << " : is false because no rule validate it" << std::endl;
		return (ret);
	}
}

void					Creator::execute(void)
{
	char				res = false;
	char				query;

	if (this->_queries.size() == 0)
		return ;
	query = *(this->_queries.begin());
	std::cout << "For query : " << query << std::endl;
	res = check_all(query);
	this->_result_query.insert(this->_result_query.end(), std::pair<char, bool>(query, res));
	this->_queries.erase(this->_queries.begin());
	std::cout << std::endl;
	this->execute();
}

void					Creator::start_execute(void)
{
	std::map<char, bool>::iterator	it;

	this->execute();
	std::cout << std::endl;
	it = this->_result_query.begin();
	while (it != this->_result_query.end())
	{
		std::cout << (it->second == true ? "\x1b[32m" : "\x1b[31m");
		std::cout << it->first << " is " << (it->second == true ? "true" : "false") << std::endl;
		std::cout << "\x1b[0m";
		it++;
	}
}