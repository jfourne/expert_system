/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creator.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:43:37 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/05 10:23:16 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATOR_CLASS_HPP
# define CREATOR_CLASS_HPP

#include "expert_system.hpp"
#include "Tree.class.hpp"

class 				Creator
{
	public:
		Creator();
		Creator(Creator const &src);
		~Creator();

		Creator			&operator=(Creator const &rhs);
		void			free_tree(Tree *tree);
		void			add_fact(char fact);
		void			add_query(char query);
		int				create_rule(char res, std::vector<t_tok *> &tokens);
		void			create_equal_rule(char res, char equal);
		char			check_equal_rule(char &query);
		bool			check_rules(char &query);
		bool			check_all(char &query);
		void			execute(void);
		// std::multimap<char, Tree *>::iterator	try_rules(char &query);

	private:
		Tree						_tree;
		std::vector<char>			_facts;
		std::vector<char>			_queries;
		std::vector<t_tok *>		_tokens;
		std::multimap<char, char>	_equal_rules;
		std::multimap<char, Tree *>	_rules;
};

#endif