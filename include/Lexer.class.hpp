/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:05:27 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/13 10:47:47 by jfourne          ###   ########.fr       */
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
		bool				free_result(std::vector<t_tok *> &result);
		int					resolve_it(void);
		t_tok*				push_result(std::string &line);
		int					create_tok(tok_type type, char value);
		t_tok*				create_tokens(tok_type type, char value);
		std::vector<t_tok *>	get_result(std::string line);
		int					get_tokens(std::string line);
		int					reduce_bracket(std::string &line, int i);
		int					check_bracket(std::string &line);
		int					search_op(std::string line, char op);
		int					check_op(std::string &line, int i);
		int					check_val(std::string &line, int &i);
		bool				check_result_in_token(char result);
		void				add_rule_symbols(char result);
		bool				check_rule_symbols(char result);
		bool				check_infinite_loop_result_symbol(char result,
									std::vector<char>::iterator its);
		bool				tokenize_line(std::string &line);
		void				tokenize_facts(std::string &line);
		void				tokenize_queries(std::string &line);

	private:
		Lexer();
		Creator							_creator;
		std::map<tok_type, char>		_op;
		std::vector<std::vector<char> >	_symbols;
		std::vector<std::string>		_lines;
		std::vector<t_tok *>			_tokens;
};

#endif