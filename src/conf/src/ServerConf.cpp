/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:44:11 by lvicino           #+#    #+#             */
/*   Updated: 2025/08/05 14:23:48 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConf.hpp"


// Constructor

ServerConf::ServerConf(void)
{
	return ;
}

ServerConf::ServerConf(int argc, char **argv)
{
	/*####################################*/
	_conf_list.push_back(Conf("0"));
	_conf_list.push_back(Conf("1"));
	return ;
	/*####################################*/

	if (argc != 2)
		throw ArgException();

	std::ifstream	conf_file(argv[1], std::ifstream::in);

	if (!conf_file)
		throw CantOpenFileException(argv[1]);
	else
		std::cerr << "Opened '" << argv[1] << "'" << std::endl;

	std::string	buffer, content;

	while (getline(conf_file, buffer))
		content += buffer + "\n";

	// in progress

	return ;
}

ServerConf::ServerConf(const ServerConf &other)
{
	*this = other;
	return ;
}

ServerConf::~ServerConf(void)
{
	return ;
}


// Operator

ServerConf	&ServerConf::operator=(const ServerConf &other)
{
	_conf_list = other ._conf_list;
	return (*this);
}


// Fonction

std::vector<Conf>	ServerConf::getConfList(void) const
{
	return (_conf_list);
}


// Exception

const char	*ServerConf::ArgException::what() const throw()
{
	return("Error: webserv needs one argument");
}

const char	*ServerConf::CantOpenFileException::what() const throw()
{
	return(_error.c_str());
}
