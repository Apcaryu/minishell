/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:04:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/10 13:04:09 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include "main.h"

typedef enum e_builtins
{
	echo = 0,
	cd = 1,
	pwd = 2,
	export = 3,
	unset = 4,
	env = 5,
}	t_builtins;

void	echo_exec(t_elem_pars *elem);
void	cd_exec(t_elem_pars *elem);
void	pwd_exec(void);
void	export_exec(char *str);
void	unset_exec(char *str);
void	env_exec(void);
void	exit_exec(t_exec *exec);

#endif