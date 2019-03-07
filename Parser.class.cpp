/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:24:12 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/07 11:07:43 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

Parser::Parser(char *file): _line_nb(0), _file(file)
{
	this->_op[AND] = '+';
	this->_op[OR] = '|';
	this->_op[XOR] = '^';

	this->_line_types[RULE] = false;
	this->_line_types[FACT] = false;
	this->_line_types[QUERY] = false;
}

Parser::Parser(Parser const &src)
{
	*this = src;
}

Parser::~Parser(void)
{
	this->_op.clear();
	this->_line_types.clear();
	this->_lines.clear();
	this->_error_list.clear();
}

Parser&					Parser::operator=(Parser const &rhs)
{
	this->_line_nb = rhs._line_nb;
	this->_op = rhs._op;
	this->_line_types = rhs._line_types;
	this->_file = rhs._file;
	this->_lines = rhs._lines;
	this->_error_list = rhs._error_list;
	return *this;
}

void					Parser::add_error(std::string error)
{
	std::string			create_error;

	create_error = "Line " + std::to_string(this->_line_nb) + " : ";
	create_error += error;
	this->_error_list.push_back(create_error);
}

int						Parser::print_error(void)
{
	std::vector<std::string>::iterator	it = this->_error_list.begin();

	while (it != this->_error_list.end())
	{
		std::cerr << *it << std::endl;
		it++;
	}
	return (EXIT_FAILURE);
}

// Start the lexer if the file is good

int						Parser::start_prog(void)
{
	Lexer				lex(this->_lines);

	return (lex.resolve_it());
}

// Remove whitespace and comments from the line

void					Parser::prepare_line(std::string &line)
{
	size_t				found;

	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
	line.erase(std::remove(line.begin(), line.end(), '\v'), line.end());
	found = line.find('#');
	if (found != std::string::npos)
		line.erase(found, line.size());
}

// First parse all errors that can happen with bracket

void					Parser::parse_open_bracket(std::string &line, size_t i)
{
	std::map<tok_type, char>::iterator	it = this->_op.begin();

	if (i + 1 == line.size())
		this->add_error("opening bracket at end of line");
	while (it != this->_op.end())
	{
		if (line[i + 1] == it->second)
			this->add_error("opening bracket before an operator");
		it++;
	}	
}

void					Parser::parse_close_bracket(std::string &line, size_t i)
{
	std::map<tok_type, char>::iterator	it = this->_op.begin();

	if (i == 0)
		this->add_error("closing bracket at the beginning of the line");
	else if (line[i - 1] == '(')
		this->add_error("closing bracket right after an opening bracket");
	while (it != this->_op.end())
	{
		if (line[i - 1] == it->second)
			this->add_error("closing bracket after an operator");
		it++;
	}	
}

void					Parser::parse_inside_bracket(char curr, int &found_sign)
{
	std::map<tok_type, char>::iterator	it;

	it = this->_op.begin();
	while (it != this->_op.end())
	{
		if (curr == it->second)
			found_sign++;
		it++;
	}	
}

void					Parser::parse_bracket(std::string &line)
{
	size_t				i = 0;
	bool				inside_bracket = false;
	int					found_sign = 0;
	int					count_bracket = 0;
	int					count = 0;

	while (i < line.size())
	{
		if (line[i] == '(')
		{
			count++;
			count_bracket++;
			inside_bracket = true;
			this->parse_open_bracket(line, i);
		}
		else if (line[i] == ')')
		{
			count--;
			if (count == 0)
				inside_bracket = false;
			this->parse_close_bracket(line, i);
		}
		if (inside_bracket == true)
			parse_inside_bracket(line[i], found_sign);
		i++;
	}
	if (found_sign < count_bracket)
		this->add_error("no sign found inside bracket");
	if (count != 0)
		this->add_error("incorrect number of brackets");
}

void					Parser::parse_pre_equal(std::string line)
{
	size_t				found;
	std::regex			check_rule("^(!?[A-Z](\\+|\\||\\^))+!?[A-Z]$");

	found = line.find("=>");
	if (found != std::string::npos)
		line.erase(found, line.size());
	line.erase(std::remove(line.begin(), line.end(), '('), line.end());
	line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
	if (line.size() == 1)
	{
		if (std::regex_match(line, std::regex("^[A-Z]$")))
			return ;
		this->add_error("can't have only operator in the rule");
		return ;
	}
	if (std::regex_match(line, check_rule))
		return ;
	this->add_error("parsing error in the rule");
}

void					Parser::parse_post_equal(std::string line)
{
	size_t				found;
	std::string			result_op = "=>";
	std::regex			check_rule("^([A-Z]\\+)+[A-Z]$");

	found = line.find("=>");
	if (found != std::string::npos)
		line.erase(0, found + result_op.size());
	line.erase(std::remove(line.begin(), line.end(), '('), line.end());
	line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
	if (line.size() == 1)
	{
		if (std::regex_match(line, std::regex("^[A-Z]$")))
			return ;
		this->add_error("can't have only operator in the result");
		return ;
	}
	if (std::regex_match(line, check_rule))
		return ;
	this->add_error("parsing error in the result");
}

void					Parser::parse_fact_query(std::string line)
{
	if (std::regex_match(line, std::regex("^(=|\\?)[A-Z]*$")))
		return ;
	if (line[0] == '=')
		this->add_error("parsing error in fact line");
	else
		this->add_error("parsing error in query line");
}

// Identify which type of line has to be parsed

void					Parser::identify_line(std::string line)
{
	size_t				found;

	found = line.find("=>");
	if (found != std::string::npos)
	{
		this->parse_pre_equal(line);
		this->parse_post_equal(line);
		this->_line_types[RULE] = true;
	}
	found = line.find("=");
	if (found != std::string::npos && found == 0)
	{
		this->parse_fact_query(line);
		this->_line_types[FACT] = true;
	}
	found = line.find("?");
	if (found != std::string::npos && found == 0)
	{
		this->parse_fact_query(line);
		this->_line_types[QUERY] = true;
	}
}

void					Parser::parse_line(std::string &line)
{
	this->_line_nb++;
	this->prepare_line(line);
	this->parse_bracket(line);
	if (line.size() > 0)
	{
		this->identify_line(line);
		this->_lines.push_back(line);
	}
}

void					Parser::found_all_line_type(void)
{
	if (this->_line_types[RULE] == false)
		this->add_error("parsing error : no rule section");
	if (this->_line_types[FACT] == false)
		this->add_error("parsing error : no fact section");
	if (this->_line_types[QUERY] == false)
		this->add_error("parsing error : no query section");
}

int						Parser::open_file(void)
{
	std::ifstream		ifs;
	std::string			line;

	ifs.open(this->_file);
	if (ifs.is_open())
	{
		while (std::getline(ifs, line))
			this->parse_line(line);
		this->found_all_line_type();
		if (this->_error_list.size() > 0)
			return (this->print_error());
	}
	return (this->start_prog());
}