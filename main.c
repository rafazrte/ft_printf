/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarate <rzarate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 22:12:08 by rzarate           #+#    #+#             */
/*   Updated: 2018/03/08 10:28:39 by rzarate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	main(void)
{
	char	c = 'r';
	long	int	i = 10;
	char	i2 = 110;

	int n = ft_printf("LOL %#-10.657li %0-5.800hhi %c\n", i, i2, c);
	int n2 = printf("LOL %+10li %-1.23hhi %c\n", i, i2, c);
	ft_putchar('\n');
	printf("ft_printf: %i\tprintf: %i", n, n2);
	while (1)
		n++;
	return (1);
}
