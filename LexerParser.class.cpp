/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:06:20 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/04 13:57:24 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LexerParser.class.hpp"

LexerParser::LexerParser()
{
}

LexerParser::LexerParser(LexerParser const &src)
{
	*this = src;
}

LexerParser::~LexerParser()
{
	std::vector<t_tok *>::iterator		it = this->_tokens.begin();

	while (it != this->_tokens.end())
	{
		free(*it);
		it++;
	}
	this->_tokens.clear();
	this->_error_list.clear();
}

LexerParser&			LexerParser::operator=(LexerParser const &rhs)
{
	this->_creator = rhs._creator;
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

void					LexerParser::parse_line()
{
	this->_creator.add_fact('C');
	this->_creator.add_fact('A');
	this->_creator.add_fact('B');
	if (this->create_tok(AND, '+') == EXIT_FAILURE)
		free_all();
	if (this->create_tok(VAL, 'A') == EXIT_FAILURE)
		free_all();
	if (this->create_tok(VAL, 'B') == EXIT_FAILURE)
		free_all();
	this->_creator.create_rule('D', this->_tokens);
	this->_creator.add_query('C');
	this->_creator.add_query('D');
	// this->_creator.add_fact('F');
	// this->_creator.add_fact('I');
}

int						LexerParser::open_file(char *file)
{
	std::ifstream		ifs;

	ifs.open(file);
	if (ifs.is_open())
	{
		// while (std::getline(ifs, this->_line))
		this->parse_line();
		if (this->_error_list.size() > 0)
			return (EXIT_FAILURE);
		else
		{
			this->_creator.execute();
		}
	}
	return (EXIT_SUCCESS);
}