/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_y(double tex_pos, int height)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= height)
		tex_y = height - 1;
	return (tex_y);
}

static void	render_door_pixel(t_game *game, t_ray *ray, int x, t_img *texture)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end && y < HEIGHT)
	{
		color = get_texture_pixel(texture, ray->tex_x,
				get_texture_y(tex_pos, texture->height));
		tex_pos += step;
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&game->img, x, y + (int)(game->player.pitch * 200), color);
		y++;
	}
}

static int	get_door_tex_x(t_ray *ray, t_door *door, t_img *texture)
{
	int	slide_offset_x;
	int	visible_tex_width;
	int	tex_x;

	slide_offset_x = (int)(door->animation_progress * texture->width);
	visible_tex_width = texture->width - slide_offset_x;
	if (visible_tex_width <= 0)
		return (-1);
	tex_x = ray->tex_x;
	if (tex_x >= visible_tex_width)
		return (-1);
	tex_x += slide_offset_x;
	if (tex_x >= texture->width)
		return (-1);
	return (tex_x);
}

static void	draw_sliding_door(t_game *game, t_ray *ray, int x, t_door *door)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;
	int		tex_x;

	tex_x = get_door_tex_x(ray, door, &game->door_closed_texture);
	if (tex_x < 0)
		return ;
	step = 1.0 * game->door_closed_texture.height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end && y < HEIGHT)
	{
		color = get_texture_pixel(&game->door_closed_texture, tex_x,
				get_texture_y(tex_pos, game->door_closed_texture.height));
		tex_pos += step;
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&game->img, x, y + (int)(game->player.pitch * 200), color);
		y++;
	}
}

void	draw_door_column(t_game *game, t_ray *ray, int x)
{
	t_door	*door;
	t_img	*door_texture;

	door = find_door(game, ray->map_x, ray->map_y);
	if (door && door->state == DOOR_OPEN)
		return ;
	door_texture = &game->door_closed_texture;
	if (!door_texture->img || !door_texture->addr)
	{
		draw_wall_column(game, ray, x);
		return ;
	}
	if (door && (door->state == DOOR_OPENING || door->state == DOOR_CLOSING))
		draw_sliding_door(game, ray, x, door);
	else
		render_door_pixel(game, ray, x, door_texture);
}
