/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manageflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:44:28 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:44:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "err.h"

void	find_and_start_func(t_ssl_mngr mngr[], int argc, char **argv, int flag)
{
	int i;

	i = -1;
	while (++i < POINTERFUNC)
	{
		// ft_printf("(%i)seg: %s\n", i, *(argv + 1));
		if (*(argv + 1) != NULL  && ft_strequ(*(argv + 1), mngr[i].conver))
		{
			mngr[i].mngr(argc, argv, i);
			// ft_printf("===seg\n");
			flag++;
		}
	}
	if (flag != 1)
		print_error(argv);

}

void	flag_parser(int argc, char **argv, int flag)
{
	static t_ssl_mngr	(mngr[POINTERFUNC]) = {
		{ .conver = "md5", .mngr = start_md },
		{ .conver = "sha256", .mngr = start_md },
		{ .conver = "whirlpool", .mngr = start_md },
		{ .conver = "base64", .mngr = start_base64 },
		{ .conver = "des", .mngr = start_ecb },
		{ .conver = "des-ecb", .mngr = start_ecb },
		{ .conver = "des-cbc", .mngr = start_cbc },
		{ .conver = "des3", .mngr = start_des3cbc },
		{ .conver = "des3-cbc", .mngr = start_des3cbc },
		{ .conver = "des3-ecb", .mngr = start_des3ecb },
		{ .conver = "genrsa", .mngr = start_genrsa },
		{ .conver = "rsa", .mngr = start_rsa },
		{ .conver = "rsautl", .mngr = start_rsautl },
		};

	find_and_start_func(mngr, argc, argv, flag);
}

void	read_input(t_ssl *data, UC **inp, size_t *size)
{
	if ((data->inp == NULL) || ((data->inp) && (ft_strequ(data->inp, "-"))))
	{
		*inp = input_read(size);
		if (*size < 1)
		{
			ft_printf("ERROR! No input data\n");
			exit(1);
		}
	}
	else
		*inp = readoutfile(data->inp, size);
}
