/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:05:27 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/05 10:23:28 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXERPARSER_CLASS_HPP
# define LEXERPARSER_CLASS_HPP

#include "expert_system.hpp"
#include "Creator.class.hpp"

class LexerParser
{
	public:
		LexerParser();
		LexerParser(LexerParser const &src);
		~LexerParser();

		LexerParser			&operator=(LexerParser const &rhs);

		int					open_file(char *file);
		int					create_tok(tok_type type, char value);
		void				tokenize_line(std::string &line);
		void				prepare_line(std::string &line);
		std::vector<char>	get_result(std::string line);
		void				get_tokens(std::string line);
		int					check_bracket(std::string &line);
		int					check_op(std::string line, int i);
		void				check_val(std::string &line, int &i);
		void				reduce_bracket(std::string &line, int i);

	private:
		Creator						_creator;
		std::map<tok_type, char>	_op;
		std::string					_line;
		std::vector<t_tok *>		_tokens;
		std::vector<std::string>	_error_list;
};

#endif