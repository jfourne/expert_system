/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creator.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:43:37 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/20 10:15:42 by jfourne          ###   ########.fr       */
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
		int				create_rule(t_tok * res, std::vector<t_tok *> &tokens);
		void			create_equal_rule(t_tok * res, char equal, bool valid);
		char			check_equal_rule(char &query);
		bool			check_rules(char &query);
		bool			check_all(char &query);
		void			execute(void);
		void			start_execute(void);

	private:
		Tree						_tree;
		std::map<char, bool>		_result_query;
		std::vector<char>			_facts;
		std::vector<char>			_queries;
		std::multimap<t_tok *, t_tok *>	_equal_rules;
		std::multimap<t_tok *, Tree *>	_rules;
};

#endif