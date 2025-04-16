/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letsgoski.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:13:49 by mbrighi           #+#    #+#             */
/*   Updated: 2025/04/16 16:31:10 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	rendering(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1' || game->map[y][x] == '0' \
				|| game->map[y][x] == 'E' || game->map[y][x] == 'C' \
				|| game->map[y][x] == 'P' || game->map[y][x] == 'G')
				letsfill(game, x, y);
			x++;
		}
		y++;
	}
	player_do_things(game);
}
void	player_do_things(t_game *game)
{
	if (!game->pg.pg_is_dead && !game->pg.pg_is_going_out)
		mlx_put_image_to_window(game->mlx, game->window,
			game->pg.pg[game->pg.idx_pg], game->pg.pg_start_x * PIX,
			game->pg.pg_start_y * PIX);	
	if (game->pg.pg_is_dead)
		mlx_put_image_to_window(game->mlx, game->window,
			game->pg.death[game->pg.idx_death], game->pg.pg_start_x * PIX,
			game->pg.pg_start_y * PIX);
	if(!game->pg.pg_is_going_out && !game->pg.no_more_coll)
		mlx_put_image_to_window(game->mlx, game->window,
			game->stat_exit[0], game->exit_x * PIX, game->exit_y * PIX);
	if (game->pg.pg_is_going_out && !game->pg.no_more_coll)
		mlx_put_image_to_window(game->mlx, game->window,
			game->stat_exit[1], game->exit_x * PIX,
			game->exit_y * PIX);
	if(!game->pg.pg_is_going_out && game->pg.no_more_coll)
		mlx_put_image_to_window(game->mlx, game->window,
			game->stat_exit[2], game->exit_x * PIX,
			game->exit_y * PIX);
	if (game->pg.no_more_coll && game->pg.pg_is_going_out)
		mlx_put_image_to_window(game->mlx, game->window,
			game->exit_win[game->idx_exit], game->pg.pg_start_x * PIX,
			game->pg.pg_start_y * PIX);	
}

void	letsfill(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->window,
			game->img.wall, x * PIX, y * PIX);
	else if (game->map[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->window,
			game->img.floor, x * PIX, y * PIX);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->window,
			game->img.coll, x * PIX, y * PIX);
	else if (game->map[y][x] == 'G')
		mlx_put_image_to_window(game->mlx, game->window,
			game->gob[game->idx_gob], x * PIX, y * PIX);
}

void	letsgoski(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, game->columns * PIX,
			game->rows * PIX, "so_long");
	if (game->window == NULL)
		ft_printf("There's no map up here\n");
	if (game->window == NULL)
	{
		ft_printf("Failed map\n");
		exit (0);
	}
	initialize_img(game);
	rendering(game);
	mlx_key_hook(game->window, handle_key, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
}
