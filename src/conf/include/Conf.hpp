/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:28:28 by lvicino           #+#    #+#             */
/*   Updated: 2025/08/04 16:05:51 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP

# include "ErrorPath.hpp"

class	Conf
{
	private:
		Conf(void);

		std::string					_host;
		std::string					_port;
		std::string					_root;
		std::vector<std::string>	_server_name;
		std::vector<ErrorPath>		_error;
		int							_max_request_size;

		// const char					*_list[6] = 
		// {"listen", "server_name", "root", "index", 
		// "error_page", "client_max_body_size"};

	public:
		Conf(const std::string &conf);
		Conf(const Conf &other);

		~Conf(void);

		Conf	&operator=(const Conf &other);

		std::string					getHost(void) const;
		std::string					getPort(void) const;
		std::string					getRoot(void) const;
		std::vector<std::string>	getServerName(void) const;
		std::vector<ErrorPath>		getError(void) const;
		int							getMaxRequestSize(void) const;
};

#endif
