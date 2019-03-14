/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:00:11 by jfourne           #+#    #+#             */
/*   Updated: 2019/03/13 10:59:28 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <iostream>
#include "Parser.class.hpp"

int			main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "expert system can only take a file as parameter" << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		Parser		parser(av[1]);
		parser.open_file();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (EXIT_SUCCESS);
}
