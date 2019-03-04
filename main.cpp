/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:00:11 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/04 13:57:57 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <iostream>
#include "LexerParser.class.hpp"

int			main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "expert system can only take a file as parameter" << std::endl;
		return (EXIT_FAILURE);
	}

	LexerParser		lp;
	lp.open_file(av[1]);
	return (EXIT_SUCCESS);
}