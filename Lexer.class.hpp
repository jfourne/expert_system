/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:05:27 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/07 11:07:53 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_CLASS_HPP
# define LEXER_CLASS_HPP

#include "expert_system.hpp"
#include "Creator.class.hpp"

class Lexer
{
	public:
		Lexer(std::vector<std::string> lines);
		Lexer(Lexer const &src);
		~Lexer();

		Lexer			&operator=(Lexer const &rhs);

		void				free_tokens(void);
		int					resolve_it(void);
		int					create_tok(tok_type type, char value);
		std::vector<char>	get_result(std::string line);
		int					get_tokens(std::string line);
		void				reduce_bracket(std::string &line, int i);
		int					check_bracket(std::string &line);
		int					check_op(std::string line, int i);
		int					check_val(std::string &line, int &i);
		bool				check_result_in_token(char result);
		bool				tokenize_line(std::string &line);
		void				tokenize_facts(std::string &line);
		void				tokenize_queries(std::string &line);

	private:
		Lexer();
		Creator						_creator;
		std::map<tok_type, char>	_op;
		std::vector<std::string>	_lines;
		std::vector<t_tok *>		_tokens;
};

#endif