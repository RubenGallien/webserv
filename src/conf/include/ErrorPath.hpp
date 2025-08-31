/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPath.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:48:10 by lvicino           #+#    #+#             */
/*   Updated: 2025/08/04 16:52:22 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORPATH_HPP
# define ERRORPATH_HPP

# include <vector>
# include <sstream>
# include <climits>
# include <cstdlib>

# include <iostream>

class	ErrorPath
{
	private:
		ErrorPath(void);

		std::string			_path;
		std::vector<int>	_error_id;

	public:
		ErrorPath(const std::string &str);
		ErrorPath(const ErrorPath &other);

		~ErrorPath(void);

		ErrorPath	&operator=(const ErrorPath &other);

		std::string			getPath(void) const;
		std::vector<int>	getErrorId(void) const;

		class	ArgException : public std::exception
		{
			const char	*what() const throw();
		};

		class	InvalidValueException : public std::exception
		{
			std::string _error;

			const char	*what() const throw();

			public:
				virtual ~InvalidValueException() throw() {}

				InvalidValueException(const std::string &value) :
				_error("Error: [emerg] invalid value \"" + value + "\"") {}
		};
};

#endif
