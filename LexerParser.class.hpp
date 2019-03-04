/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:05:27 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/01 15:47:47 by jfourne          ###   ########.fr       */
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
		void				parse_line();

	private:
		Creator						_creator;
		std::string					_line;
		std::vector<t_tok *>		_tokens;
		std::vector<std::string>	_error_list;
};

#endif