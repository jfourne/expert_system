/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeBrowser.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:25:19 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/04 17:55:37 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEBROWSER_CLASS_HPP
# define TREEBROWSER_CLASS_HPP

#include "Creator.class.hpp"
#include "Tree.class.hpp"

class				TreeBrowser
{
	public:
		TreeBrowser(Creator *creator);
		TreeBrowser(TreeBrowser const &src);
		~TreeBrowser();

		TreeBrowser&			operator=(TreeBrowser const &rhs);
		bool					check_conditions(bool left, bool right, Tree *tree);
		bool					browse_tree(Tree *tree);

	private:
		TreeBrowser() {};
		Creator		*_creator;
};

#endif