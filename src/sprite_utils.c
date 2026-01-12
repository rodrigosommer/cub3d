/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/10/13 18:19:20 by mlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calc_sprite_dist(t_game *game, int i)
{
	return ((game->sprites[i].x - game->player.x)
		* (game->sprites[i].x - game->player.x)
		+ (game->sprites[i].y - game->player.y)
		* (game->sprites[i].y - game->player.y));
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_sprites_by_distance(t_game *game)
{
	int		i;
	int		j;
	double	dist_i;
	double	dist_j;

	i = 0;
	while (i < game->num_sprites - 1)
	{
		j = i + 1;
		while (j < game->num_sprites)
		{
			dist_i = calc_sprite_dist(game, i);
			dist_j = calc_sprite_dist(game, j);
			if (dist_i < dist_j)
				swap_sprites(&game->sprites[i], &game->sprites[j]);
			j++;
		}
		i++;
	}
}

static void	render_sprite_columns(t_game *game, int i, int start_x, int end_x,
	int sprite_size)
{
	while (start_x < end_x)
	{
		draw_sprite_column(game, &game->sprites[i], start_x, sprite_size);
		start_x++;
	}
}

void	render_sprites(t_game *game)
{
	int		i;
	int		sprite_screen_x;
	double	sprite_size;
	int		start_x;
	int		end_x;

	update_sprites(game);
	sort_sprites_by_distance(game);
	i = 0;
	while (i < game->num_sprites)
	{
		calc_sprite_screen_pos(game, &game->sprites[i],
			&sprite_screen_x, &sprite_size);
		if (sprite_size > 0)
		{
			calc_sprite_bounds(&start_x, &end_x, sprite_screen_x, sprite_size);
			render_sprite_columns(game, i, start_x, end_x, (int)sprite_size);
		}
		i++;
	}
}
