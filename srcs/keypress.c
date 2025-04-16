/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:53:56 by mbrighi           #+#    #+#             */
/*   Updated: 2025/04/17 01:07:16 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 65307)
	{
		ft_printf("I spent lot of time on this game! Play it, please!\n");
		kill_em_all(game);
	}
	if (keycode == 119 || keycode == 65362)
		move_player(param, 0, -1, 0);
	if (keycode == 115 || keycode == 65364)
		move_player(param, 0, 1, 1);
	if (keycode == 97 || keycode == 65361)
		move_player(param, -1, 0, 2);
	if (keycode == 100 || keycode == 65363)
		move_player(param, 1, 0, 3);
	return (0);
}

void	move_player(t_game *game, int dx, int dy, int move)
{
	int		new_x;
	int		new_y;
	char	next_pos;

	new_x = game->pg.pg_start_x + dx;
	new_y = game->pg.pg_start_y + dy;
	next_pos = game->map[new_y][new_x];
	if (can_move_to(game, new_x, new_y) == 1)
	{
		if (next_pos == 'C')
			game->coll_coll++;
		game->map[game->pg.pg_start_y][game->pg.pg_start_x] = '0';
		game->map[new_y][new_x] = 'P';
		game->pg.pg_start_x = new_x;
		game->pg.pg_start_y = new_y;
		game->pg.pg_moves++;
	}
	if (move == 0)
		mlx_string_put(game->mlx, game->win, 50, 50, 0xFFFFFF, "Moving Up");
	if (move == 1)
		mlx_string_put(game->mlx, game->win, 50, 50, 0xFFFFFF, "Moving Down");
	if (move == 2)
		mlx_string_put(game->mlx, game->win, 50, 50, 0xFFFFFF, "Moving Sx");
	if (move == 3)
		mlx_string_put(game->mlx, game->win, 50, 50, 0xFFFFFF, "Moving Dx");
}

int	can_move_to(t_game *game, int x, int y)
{
	if (x <= 0 || y <= 0 || x >= (int)game->columns || y >= (int)game->rows)
		return (0);
	if (game->pg.pg_is_going_out && game->pg.no_more_coll)
		return (0);
	if (game->map[y][x] == '1')
		return (0);
	if (game->map[y][x] == 'E' && game->pg.pg_is_dead)
		return (0);
	if (game->map[y][x] == 'G')
	{
		game->pg.pg_is_dead = 1;
		return (0);
	}
	return (1);
}
