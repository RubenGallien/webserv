/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:28:30 by lvicino           #+#    #+#             */
/*   Updated: 2025/08/05 14:24:38 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conf.hpp"

// Constructor

Conf::Conf(void)
{
	return;
}

Conf::Conf(const std::string &conf) :
_host("127.0.0.1"), _port("8888"), _max_request_size(1024) // needs to recieve the content of a server block
{
	/*####################################*/
	if (conf == "0")
	{
		_host = "127.0.0.1";
		_port = "8888";
		_root = "nothing";
		_server_name.push_back("localhost");
		_error.push_back(ErrorPath("404 403	img/katt.jpg"));
		_max_request_size = 1024;
	}
	else if (conf == "1")
	{
		_host = "127.0.0.1";
		_port = "8889";
		_root = "nothing";
		_server_name.push_back("localhost");
		_error.push_back(ErrorPath("404 403	img/katt.jpg"));
		_max_request_size = 1024;
	}
	return ;
	/*####################################*/

	// std::istringstream	iss(conf);
	// std::string			word;

	// while (iss >> word)
	// {
	// 	for (int i = 0; i < 6; i++)
	// 	{
	// 		if (_list[i] == word)
	// 		{
	// 			// get var info
	// 			while (iss >> word)
	// 			{
	// 				if (word.back() == ';')
	// 					break ;
	// 			}
	// 			break ;
	// 		}
	// 		else if (i == 6)
	// 			throw;
	// 	}
	// }
	return ;
}

Conf::Conf(const Conf &other)
{
	*this = other;
	return;
}

Conf::~Conf(void)
{
	return ;
}

// Operator

Conf &Conf::operator=(const Conf &other)
{
	_host = other._host;
	_port = other._port;
	_root = other._root;
	_server_name = other._server_name;
	_error = other._error;
	_max_request_size = other._max_request_size;
	return (*this);
}


// Fonction

std::string	Conf::getHost(void) const
{
	return (_host);
}

std::string	Conf::getPort(void) const
{
	return (_port);
}

std::string	Conf::getRoot(void) const
{
	return (_root);
}

std::vector<std::string>	Conf::getServerName(void) const
{
	return (_server_name);
}

std::vector<ErrorPath>	Conf::getError(void) const
{
	return (_error);
}

int	Conf::getMaxRequestSize(void) const
{
	return (_max_request_size);
}
