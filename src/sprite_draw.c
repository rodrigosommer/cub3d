/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/10/09 18:35:00 by mlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_draw(t_sprite_draw *sd, t_game *game, t_sprite *sp,
	int sprite_size)
{
	int		sprite_screen_x;
	double	temp_size;
	int		y_offset;

	calc_sprite_screen_pos(game, sp, &sprite_screen_x, &temp_size);
	sd->dist = sqrt((sp->x - game->player.x) * (sp->x - game->player.x)
			+ (sp->y - game->player.y) * (sp->y - game->player.y));
	y_offset = 0;
	if (sp->is_dead)
		y_offset = sprite_size / 2;
	sd->start_y = (HEIGHT - sprite_size) / 2 + y_offset;
	sd->end_y = (HEIGHT + sprite_size) / 2 + y_offset;
	if (sd->start_y < 0)
		sd->start_y = 0;
	if (sd->end_y >= HEIGHT)
		sd->end_y = HEIGHT - 1;
	sd->screen_x = sprite_screen_x;
}

static int	get_texture_id(t_sprite *sprite)
{
	int	texture_to_use;

	texture_to_use = sprite->texture_id;
	if (texture_to_use < 0 || texture_to_use >= 6)
		texture_to_use = 0;
	if (sprite->texture_id == 0 && sprite->frame == 1 && !sprite->is_dead)
		texture_to_use = 5;
	return (texture_to_use);
}

static int	is_transparent_pixel(int color, int tex_id)
{
	if (tex_id == 4 || tex_id == 5)
	{
		if (color == 0x000000 || color == 0xFF00FF || color == 0xE800FF
			|| color == 0 || color == 0xFFFFFF)
			return (1);
	}
	else
	{
		if (color == 0xFF00FF || color == 0x00FF00FF || color == 0)
			return (1);
	}
	return (0);
}

static void	draw_sprite_pixels(t_game *game, t_sprite_draw *sd, int x,
	int sprite_size)
{
	int	y;
	int	tex_y;
	int	color;
	int	pitch_offset;
	int	final_y;

	y = sd->start_y;
	while (y <= sd->end_y)
	{
		tex_y = (int)((y - sd->start_y)
				* game->sprite_textures[sd->tex_id].height / sprite_size);
		if (tex_y >= 0 && tex_y < game->sprite_textures[sd->tex_id].height)
		{
			color = get_texture_pixel(&game->sprite_textures[sd->tex_id],
					sd->tex_x, tex_y);
			if (!is_transparent_pixel(color, sd->tex_id))
			{
				pitch_offset = (int)(game->player.pitch * 100);
				final_y = y + pitch_offset;
				if (final_y >= 0 && final_y < HEIGHT)
					put_pixel(&game->img, x, final_y, color);
			}
		}
		y++;
	}
}

void	draw_sprite_column(t_game *game, t_sprite *sprite, int x,
	int sprite_size)
{
	t_sprite_draw	sd;

	if (x < 0 || x >= WIDTH || sprite_size <= 0)
		return ;
	init_sprite_draw(&sd, game, sprite, sprite_size);
	if (sd.dist >= game->zbuffer[x])
		return ;
	sd.tex_id = get_texture_id(sprite);
	sd.tex_x = (int)((x - (sd.screen_x - sprite_size / 2))
			* game->sprite_textures[sd.tex_id].width / sprite_size);
	if (sd.tex_x < 0 || sd.tex_x >= game->sprite_textures[sd.tex_id].width)
		return ;
	if (!game->sprite_textures[sd.tex_id].addr)
		return ;
	draw_sprite_pixels(game, &sd, x, sprite_size);
}
