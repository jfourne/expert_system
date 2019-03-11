/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:21:04 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/07 11:07:44 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <iostream>
#include <string>
#include <regex>
#include "expert_system.hpp"
#include "Lexer.class.hpp"

enum line_type {
	RULE,
	FACT,
	QUERY,
};

class				Parser
{
	public:
		Parser(char *file);
		Parser(Parser const &src);
		~Parser(void);

		Parser&			operator=(Parser const &rhs);

		int				open_file(void);
		void			found_all_line_type(void);
		void			add_error(std::string error);
		int				print_error(void);		
		int				start_prog(void);
		void			prepare_line(std::string &line);
		void			parse_open_bracket(std::string &line, size_t i);
		void			parse_close_bracket(std::string &line, size_t i);
		void			parse_inside_bracket(char curr, int &found_sign);
		void			parse_bracket(std::string &line);
		void			parse_pre_equal(std::string line);
		void			parse_post_equal(std::string line);
		void			parse_fact_query(std::string);
		void			parse_line(std::string &line);
		void			identify_line(std::string line);

	private:
		Parser() {};
		int							_line_nb;
		std::map<tok_type, char>	_op;
		std::map<line_type, bool>	_line_types;
		std::string					_file;
		std::vector<std::string>	_lines;
		std::vector<std::string>	_error_list;
};

#endif