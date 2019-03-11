/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expert_system.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:57:46 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/01 13:54:04 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERT_SYSTEM_HPP
# define EXPERT_SYSTEM_HPP

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <utility>

enum tok_type {
	AND,
	OR,
	XOR,
	VAL,
	NOT_VAL,
};

typedef struct		s_tok
{
	tok_type		type;
	char			value;
	struct s_tok	*next;
}					t_tok;

#endif