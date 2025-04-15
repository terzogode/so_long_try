/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:53:56 by mbrighi           #+#    #+#             */
/*   Updated: 2025/04/16 00:32:30 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	(void)game;
	//printf("Tasto premuto: %d\n", keycode);
	if (keycode == 65307)
		errors1(param, E_EASY_EXIT);
	if (keycode == 119 || keycode == 65362)
		move_player(param, 0, -1);
	if (keycode == 115 || keycode == 65364)
		move_player(param, 0, 1);
	if (keycode == 97 || keycode == 65361)
		move_player(param, -1, 0);
	if (keycode == 100 || keycode == 65362)
		move_player(param, 1, 0);
	return (0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int new_x;
	int new_y;
	char next_tile;

	new_x = game->pg.pg_start_x + dx;
	new_y = game->pg.pg_start_y + dy;
	next_tile = game->map[new_y][new_x];

	if (can_move_to(game, new_x, new_y) == 1) // Se può muoversi
	{
		if (next_tile == 'C') // Se c'è un collezionabile
			game->coll_coll++;
		
		// Aggiorna la mappa e sposta il giocatore
		game->map[game->pg.pg_start_y][game->pg.pg_start_x] = '0';
		game->map[new_y][new_x] = 'P';
		game->pg.pg_start_x = new_x;
		game->pg.pg_start_y = new_y;
		game->pg.pg_moves++; // Incrementa le mosse
	}
}

int	can_move_to(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1') // muro
		return (0);
	if (game->map[y][x] == 'E')
	{
		if (game->coll_coll == game->tot_coll)
			return (2); // può vincere
		else
			return (0); // uscita ma non ancora disponibile
	}
	return (1); // spazio vuoto o collezionabile
}

