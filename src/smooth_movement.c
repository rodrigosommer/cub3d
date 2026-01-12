/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_smooth(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 1;
	if (keycode == KEY_ESC)
		close_window(game);
	if (game->level_completed && keycode == KEY_ENTER)
	{
		close_window(game);
		return (0);
	}
	if (game->level_completed)
		return (0);
	if (keycode == KEY_SPACE)
		handle_katana_slash(game);
	else if (keycode == KEY_E)
		handle_door_interaction(game);
	else if (keycode == KEY_R)
		game->rainbow_enabled = !game->rainbow_enabled;
	return (0);
}

int	key_release_smooth(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

void	process_movement(t_game *game)
{
	if (game->keys[KEY_W])
		move_player(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	if (game->keys[KEY_S])
		move_player(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	if (game->keys[KEY_A])
		move_player(game, game->player.dir_y * MOVE_SPEED,
			-game->player.dir_x * MOVE_SPEED);
	if (game->keys[KEY_D])
		move_player(game, -game->player.dir_y * MOVE_SPEED,
			game->player.dir_x * MOVE_SPEED);
	if (game->keys[KEY_LEFT])
		rotate_player(game, -ROT_SPEED);
	if (game->keys[KEY_RIGHT])
		rotate_player(game, ROT_SPEED);
}
