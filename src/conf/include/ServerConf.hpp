/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:48:10 by lvicino           #+#    #+#             */
/*   Updated: 2025/08/04 16:02:54 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONF_HPP
# define SERVERCONF_HPP

# include <iostream>
# include <cstring>
# include <fstream>
// # include <cerrno> // needed for errno???

# include "Conf.hpp"

class	ServerConf
{
	private:
		ServerConf(void);

		std::vector<Conf>	_conf_list;

	public:
		ServerConf(int argc, char **argv);
		ServerConf(const ServerConf &other);

		~ServerConf(void);

		ServerConf	&operator=(const ServerConf &other);

		std::vector<Conf>	getConfList(void) const; //might need to return a pointer

		class	ArgException : public std::exception
		{
			const char	*what() const throw();
		};

		class	CantOpenFileException : public std::exception
		{
			std::string _error;

			const char	*what() const throw();

			public:
				virtual ~CantOpenFileException() throw() {}

				CantOpenFileException(const std::string &file_name) :
				_error(file_name + ": " + strerror(errno)) {}
		};
};

#endif
