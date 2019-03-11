/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:06:20 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/11 16:54:10 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.class.hpp"

Lexer::Lexer(std::vector<std::string> lines): _lines(lines)
{
	this->_op[AND] = '+';
	this->_op[OR] = '|';
	this->_op[XOR] = '^';
}

Lexer::Lexer(Lexer const &src)
{
	*this = src;
}

Lexer::~Lexer()
{
	this->_op.clear();
	this->_lines.clear();
	this->free_tokens();
}

Lexer&			Lexer::operator=(Lexer const &rhs)
{
	this->_creator = rhs._creator;
	this->_op = rhs._op;
	this->_lines = rhs._lines;
	this->_tokens = rhs._tokens;
	return *this;
}

void					Lexer::free_tokens(void)
{
	std::vector<t_tok *>::iterator		it = this->_tokens.begin();

	while (it != this->_tokens.end())
	{
		free(*it);
		it++;
	}
	this->_tokens.clear();
}

int						Lexer::create_tok(tok_type type, char value)
{
	t_tok				*tok;

	if ((tok = (t_tok *) malloc(sizeof (t_tok))) == NULL)
		return (EXIT_FAILURE);
	tok->type = type;
	tok->value = value;
	this->_tokens.push_back(tok);
	return (EXIT_SUCCESS);
}

t_tok*					Lexer::create_tokens(tok_type type, char value)
{
	t_tok				*tok;

	if ((tok = (t_tok *) malloc(sizeof (t_tok))) == NULL)
		return (NULL);
	tok->type = type;
	tok->value = value;
	return (tok);
}

// Truncate line to only get the result part

t_tok*						Lexer::push_result(std::string &line)
{
	if (line[0] == '!')
		return (this->create_tokens(NOT_VAL, line[1]));
	else
		return (this->create_tokens(VAL, line[0]));
}

std::vector<t_tok *>		Lexer::get_result(std::string line)
{
	size_t					found;
	std::string				result_op = "=>";
	std::vector<t_tok *>	result;

	found = line.find(result_op);
	if (found != std::string::npos)
		line.erase(0, found + result_op.size());
	while ((found = line.find("+") != std::string::npos))
	{
		result.push_back(this->push_result(line));
		if (line[0] == '!')
			found++;
		line.erase(0, found + 1);
	}
	result.push_back(this->push_result(line));
	return (result);
}

int						Lexer::get_tokens(std::string line)
{
	int					i = 0;

	if (line.size() == 0)
		return (EXIT_SUCCESS);
	if (line[0] == '(')
		check_bracket(line);
	else
	{
		if ((i = check_op(line, 0)) == -2)
			return (EXIT_FAILURE);
		if (check_val(line, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	get_tokens(line);
	return (EXIT_SUCCESS);
}

// Remove bracket and tokenize what is inside it

void					Lexer::reduce_bracket(std::string &line, int i)
{
	std::string			inside_bracket;

	i = this->check_op(line, i);
	if (i > -1)
	{
		inside_bracket = line.substr(1, i - 2);
		line.erase(0, i + 1);
	}
	else
	{
		inside_bracket = line.substr(1, line.size() + 1);
		line.clear();
	}
	this->get_tokens(inside_bracket);
}

// Check if there is bracket

int						Lexer::check_bracket(std::string &line)
{
	int					i = 0;
	int					bracket = 0;

	while (static_cast<size_t>(i) < line.size())
	{
		if (line[i] == '(')
			bracket++;
		if (line[i] == ')')
			bracket--;
		if (bracket == 0)
		{
			this->reduce_bracket(line, i);
			return (0);
		}
		i++;
	}
	return (0);
}

// Browse the operator list to see if there is one

int						Lexer::check_op(std::string line, int i)
{
	std::map<tok_type, char>::iterator	it;

	while (static_cast<size_t>(i) < line.size())
	{
		it = this->_op.begin();
		while (it != this->_op.end())
		{
			if (it->second == line[i])
			{
				if (this->create_tok(it->first, it->second) == EXIT_FAILURE)
				{
					this->free_tokens();
					return (-2);
				}
				return (i);
			}
			it++;
		}
		i++;
	}
	return (-1);
}

// Add the value or "not value" to tokens

int						Lexer::check_val(std::string &line, int &i)
{
	if (line[0] == '!')
	{
		if (this->create_tok(NOT_VAL, line[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (this->create_tok(VAL, line[0]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (i > -1)
		line.erase(0, i + 1);
	else
		line.clear();
	return (EXIT_SUCCESS);
}

// Check if result is in the rule to avoid infinite loop

bool					Lexer::check_result_in_token(char result)
{
	std::vector<t_tok *>::iterator it = this->_tokens.begin();

	while (it != this->_tokens.end())
	{
		if ((*it)->value == result)
			return (true);
		it++;
	}
	return (false);
}

// Begin is the result and others are all symbols found in the rule

void					Lexer::add_rule_symbols(char result)
{
	std::vector<char>	symbol;
	std::vector<t_tok *>::iterator it = this->_tokens.begin();

	symbol.push_back(result);
	while (it != this->_tokens.end())
	{
		if ((*it)->type == VAL || (*it)->type == NOT_VAL)
			symbol.push_back((*it)->value);
		it++;
	}
	this->_symbols.push_back(symbol);
}

// Check if a symbol that lead to result already has result in his symbol rule

bool					Lexer::check_infinite_loop_result_symbol(char result,
							std::vector<char>::iterator its)
{
	std::vector<std::vector<char> >::iterator	it = this->_symbols.begin();

	while (it != this->_symbols.end())
	{
		std::vector<char>::iterator	itloop = (*it).begin();
		if (itloop != (*it).end() && *itloop == *its)
		{
			itloop++;
			while (itloop != (*it).end())
			{
				if (*itloop == result)
					return (true);
				itloop++;
			}
		}
		it++;
	}
	return (false);
}

bool					Lexer::check_rule_symbols(char result)
{
	std::vector<std::vector<char> >::iterator	it = this->_symbols.begin();

	while (it != this->_symbols.end())
	{
		std::vector<char>::iterator	its = (*it).begin();
		if (its != (*it).end() && *its == result)
		{
			its++;
			while (its != (*it).end())
			{
				if (check_infinite_loop_result_symbol(result, its) == true)
					return (true);
				its++;
			}
		}
		it++;
	}
	return (false);
}

bool					Lexer::tokenize_line(std::string &line)
{
	size_t					found;
	std::vector<t_tok *>	result;

	result = this->get_result(line);
	found = line.find("=>");
	if (found != std::string::npos)
		line.erase(found, line.size());
	if (this->get_tokens(line) == EXIT_FAILURE)
		return (false);

	std::vector<t_tok *>::iterator	it = result.begin();
	while (it != result.end())
	{
		if (*it == NULL)
		{
			this->free_tokens();
			return (false);
		}
		this->add_rule_symbols((*it)->value);
		if (this->check_result_in_token((*it)->value) == true)
		{
			std::cerr << "Result " << (*it)->value << " : can't be in rule too" << std::endl;
			this->free_tokens();
			return (false);
		}
		if (this->check_rule_symbols((*it)->value) == true)
		{
			std::cerr << "Result " << (*it)->value << " : is in another rule wich lead to infinite loop" << std::endl;
			this->free_tokens();
			return (false);
		}
		if (this->_tokens.size() == 1 && (*(this->_tokens.begin()))->type == VAL)
			this->_creator.create_equal_rule(*it, (*(this->_tokens.begin()))->value, true);
		else if (this->_tokens.size() == 1 && (*(this->_tokens.begin()))->type == NOT_VAL)
			this->_creator.create_equal_rule(*it, (*(this->_tokens.begin()))->value, false);
		else
			this->_creator.create_rule(*it, this->_tokens);
		it++;
	}
	this->free_tokens();
	return (true);
}

void					Lexer::tokenize_facts(std::string &line)
{
	size_t				i = 1;

	while (i < line.size())
	{
		this->_creator.add_fact(line[i]);
		i++;
	}
}

void					Lexer::tokenize_queries(std::string &line)
{
	size_t				i = 1;

	while (i < line.size())
	{
		this->_creator.add_query(line[i]);
		i++;
	}
}

int						Lexer::resolve_it(void)
{
	std::vector<std::string>::iterator	it = this->_lines.begin();

	while (it != this->_lines.end())
	{
		if ((*it)[0] == '=')
			this->tokenize_facts(*it);
		else if ((*it)[0] == '?')
			this->tokenize_queries(*it);
		else
		{
			if (this->tokenize_line(*it) == false)
				return (EXIT_FAILURE);
		}
		it++;
	}
	this->_creator.start_execute();
	return (EXIT_SUCCESS);
}