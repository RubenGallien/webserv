/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPath.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:44:14 by lvicino           #+#    #+#             */
/*   Updated: 2025/08/05 17:24:50 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPath.hpp"


// Constructor

ErrorPath::ErrorPath(void)
{
	return ;
}

ErrorPath::ErrorPath(const std::string &str) //needs to receive the content between 'error_page' and ';'
{
	std::istringstream	iss(str);
	std::string			word;

	while (iss >> word && iss.peek() != -1)
	{
		// std::cout << "in while loup: " << iss.peek() << std::endl;
		char	*ptr;
		long	n = std::strtol(word.c_str(), &ptr, 10);

		if (*ptr || 300 > n || n > 599)
			break ;
		_error_id.push_back(n);
	}
	_path = word;
	// std::cout << "out while loup: " << iss.peek() << std::endl;
	if (iss.peek() != -1)
		throw InvalidValueException(_path);
	else if (!_error_id.size())
		throw ArgException();
	return ;
}

ErrorPath::ErrorPath(const ErrorPath &other)
{
	*this = other;
	return ;
}

ErrorPath::~ErrorPath(void)
{
	return ;
}


// Operator

ErrorPath	&ErrorPath::operator=(const ErrorPath &other)
{
	_error_id = other._error_id;
	_path = other._path;
	return (*this);
}


// Fonction

std::string	ErrorPath::getPath(void) const
{
	return (_path);
}

std::vector<int>	ErrorPath::getErrorId(void) const
{
	return (_error_id);
}


// Exception

const char	*ErrorPath::ArgException::what() const throw()
{
	return("Error:  [emerg] invalid number of arguments in \"error_page\" directive");
}

const char	*ErrorPath::InvalidValueException::what() const throw()
{
	return(_error.c_str());
}