/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:03:43 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/11 19:30:32 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
//*********************** STANDARD LIBRARIES *********************************
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"
//************************** DEFINITIONS *************************************
// typedef struct s_data{
// } t_data;
//*************************** FUNCTIONS **************************************
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
#endif
