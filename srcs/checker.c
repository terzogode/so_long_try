/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:45:07 by mbrighi           #+#    #+#             */
/*   Updated: 2025/04/17 15:08:06 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checker(char *argv, t_game *game)
{
	check_extension(argv, game);
	matrix_maker(argv, game);
	check_dimension(game);
	check_wall_lenght(game);
	check_wall_width(game);
	check_char(game);
	check_player(game);
	check_exit(game);
	check_coll(game);
	coll_dup_map(game);
	exit_dup_map(game);
	if (check_coll_reachability(game) == 0)
		errors1(game, E_UNREACHABLE_COLL);
	if (check_exit_reachability(game) == 0)
		errors1(game, E_EXIT);
	free_maptrix(game, game->coll_check);
	free_maptrix(game, game->exit_check);
}

int	check_extension(char *arg, t_game *game)
{
	int		i;
	char	*ext;
	int		ext_idx;

	ext_idx = 0;
	ext = ".ber";
	i = 0;
	while (arg[i] != '\0')
	{
		i++;
	}
	i = i - 4;
	while (ext_idx <= 4 && (arg[i] != '\0' && ext[ext_idx] != '\0'))
	{
		if (arg[i] != ext[ext_idx])
			errors(game, E_EXTENSION);
		ext_idx++;
		i++;
	}
	return (1);
}

void	check_dimension(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->rows)
	{
		if (ft_strlen(game->map[i]) != game->columns)
			errors(game, E_MAP_DIMENSION);
		i++;
	}
}

void	check_wall_lenght(t_game *game)
{
	size_t	j;

	j = 0;
	while (j < game->columns)
	{
		if (game->map[0][j] != '1' || game->map[game->rows - 1][j] != '1')
			errors(game, E_WALL);
		j++;
	}
}

void	check_wall_width(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->rows)
	{
		if (game->map[i][0] != '1' || game->map[i][game->columns - 1] != '1')
			errors(game, E_WALL);
		i++;
	}
}
