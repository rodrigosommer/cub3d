/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pres.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_key_press(int keycode, void *param)
{
	return (key_press_smooth(keycode, (t_game *)param));
}

int	on_key_release(int keycode, void *param)
{
	return (key_release_smooth(keycode, (t_game *)param));
}

int	on_close(void *param)
{
	return (close_window((t_game *)param));
}

int	on_mouse_move(int x, int y, void *param)
{
	return (mouse_move(x, y, (t_game *)param));
}

int	on_loop(void *param)
{
	return (game_loop((t_game *)param));
}
