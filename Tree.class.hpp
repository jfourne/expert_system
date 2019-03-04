/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:37:38 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/04 11:39:48 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_CLASS_HPP
# define TREE_CLASS_HPP

#include "expert_system.hpp"

class			Tree
{
	public:
		Tree();
		Tree(Tree const &src);
		~Tree();

		Tree&				operator=(Tree const &rhs);
		void				create_tree(std::vector<t_tok *> &tokens);
		void				print(int i);

		Tree					*_left;
		Tree					*_right;
		tok_type				_type;
		char					_value;
};

#endif