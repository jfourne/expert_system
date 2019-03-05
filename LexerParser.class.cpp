/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:06:20 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/05 10:28:54 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LexerParser.class.hpp"

LexerParser::LexerParser()
{
	this->_op[AND] = '+';
	this->_op[OR] = '|';
	this->_op[XOR] = '^';
}

LexerParser::LexerParser(LexerParser const &src)
{
	*this = src;
}

LexerParser::~LexerParser()
{
	// std::vector<t_tok *>::iterator		it = this->_tokens.begin();

	// while (it != this->_tokens.end())
	// {
	// 	free(*it);
	// 	it++;
	// }
	this->_tokens.clear();
	this->_error_list.clear();
}

LexerParser&			LexerParser::operator=(LexerParser const &rhs)
{
	this->_creator = rhs._creator;
	this->_op[AND] = '+';
	this->_op[OR] = '|';
	this->_op[XOR] = '^';
	this->_line = rhs._line;
	this->_error_list = rhs._error_list;
	return *this;
}

int						LexerParser::create_tok(tok_type type, char value)
{
	t_tok				*tok;

	if ((tok = (t_tok *) malloc(sizeof (t_tok))) == NULL)
		return (EXIT_FAILURE);
	tok->type = type;
	tok->value = value;
	this->_tokens.push_back(tok);
	return (EXIT_SUCCESS);
}

void					free_all()
{

}

void					LexerParser::prepare_line(std::string &line)
{
	size_t				found;

	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
	line.erase(std::remove(line.begin(), line.end(), '\v'), line.end());
	found = line.find('#');
	if (found != std::string::npos)
		line.erase(found, line.size());
}

std::vector<char>		LexerParser::get_result(std::string line)
{
	size_t				found;
	std::string			result_op = "=>";
	std::vector<char>	result;

	found = line.find(result_op);
	if (found != std::string::npos)
		line.erase(0, found + result_op.size());
	while ((found = line.find("+") != std::string::npos))
	{
		result.push_back(line[0]);
		line.erase(0, found + 1);
	}
	result.push_back(line[0]);
	return (result);
}

void					LexerParser::reduce_bracket(std::string &line, int i)
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

int						LexerParser::check_bracket(std::string &line)
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

int						LexerParser::check_op(std::string line, int i)
{
	std::map<tok_type, char>::iterator	it;

	while (static_cast<size_t>(i) < line.size())
	{
		it = this->_op.begin();
		while (it != this->_op.end())
		{
			if (it->second == line[i])
			{
				this->create_tok(it->first, it->second);
				return (i);
			}
			it++;
		}
		i++;
	}
	return (-1);
}

void					LexerParser::check_val(std::string &line, int &i)
{
	if (line[0] == '!')
		this->create_tok(NOT_VAL, line[1]);
	else
		this->create_tok(VAL, line[0]);
	if (i > -1)
		line.erase(0, i + 1);
	else
		line.clear();
}

void					LexerParser::get_tokens(std::string line)
{
	int					i = 0;

	if (line.size() == 0)
		return ;
	if (line[0] == '(')
		check_bracket(line);
	else
	{
		i = check_op(line, 0);
		check_val(line, i);
	}
	get_tokens(line);
}

void					LexerParser::tokenize_line(std::string &line)
{
	size_t				found;
	std::vector<char>	result;

	this->prepare_line(line);
	result = this->get_result(line);
	found = line.find("=>");
	if (found != std::string::npos)
		line.erase(found, line.size());
	this->get_tokens(line);

	std::vector<char>::iterator	it = result.begin();
	while (it != result.end())
	{
		if (this->_tokens.size() == 1)
			this->_creator.create_equal_rule(*it, (*(this->_tokens.begin()))->value);
		else
			this->_creator.create_rule(*it, this->_tokens);
		it++;
	}
	if (this->_tokens.size() == 1)
		free(*(this->_tokens.begin()));
	this->_tokens.clear();
}

void					add_test(Creator &creator)
{
	creator.add_fact('H');
	creator.add_fact('F');
	creator.add_query('E');
}

int						LexerParser::open_file(char *file)
{
	std::ifstream		ifs;
	// std::string			line = "(A | B) + (C + Y) => D + E ; toto";
	// std::string			line = "((A + B) + D) => C";
	std::vector<std::string>	lines;

	ifs.open(file);
	add_test(this->_creator);
	lines.push_back("A | B + C => E");
	lines.push_back("(F | G) + H => E");

	if (ifs.is_open())
	{
		// while (std::getline(ifs, this->_line))
		// this->parse_line();
		std::vector<std::string>::iterator	it = lines.begin();
		while (it != lines.end())
		{
			this->tokenize_line(*it);
			it++;
		}
		if (this->_error_list.size() > 0)
			return (EXIT_FAILURE);
		else
		{
			this->_creator.execute();
		}
	}
	return (EXIT_SUCCESS);
}