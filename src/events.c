/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

static void	handle_movement_keys(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		move_player(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	else if (keycode == KEY_S)
		move_player(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	else if (keycode == KEY_A)
		move_player(game, game->player.dir_y * MOVE_SPEED,
			-game->player.dir_x * MOVE_SPEED);
	else if (keycode == KEY_D)
		move_player(game, -game->player.dir_y * MOVE_SPEED,
			game->player.dir_x * MOVE_SPEED);
}

static void	handle_rotation_keys(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, ROT_SPEED);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_SPACE)
		handle_katana_slash(game);
	handle_movement_keys(keycode, game);
	handle_rotation_keys(keycode, game);
	render_frame(game);
	return (0);
}
