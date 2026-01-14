/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_door_solid(t_game *game, int x, int y)
{
	if (game->map[y][x] != 'D' && game->map[y][x] != 'O')
		return (0);
	return (!is_door_open(game, x, y));
}

void	calculate_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_num = WEST;
	else if (ray->side == 0 && ray->dir_x < 0)
		ray->tex_num = EAST;
	else if (ray->side == 1 && ray->dir_y > 0)
		ray->tex_num = NORTH;
	else
		ray->tex_num = SOUTH;
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x
			* (double)game->textures[ray->tex_num].width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = game->textures[ray->tex_num].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = game->textures[ray->tex_num].width - ray->tex_x - 1;
}

static void	init_wall_render(t_game *game, t_ray *ray, int *bounds,
	double *vars)
{
	int	pitch_offset;
	int	start_offset;

	pitch_offset = (int)(game->player.pitch * 200);
	bounds[0] = ray->draw_start + pitch_offset;
	bounds[1] = ray->draw_end + pitch_offset;
	vars[0] = 1.0 * game->textures[ray->tex_num].height / ray->line_height;
	vars[1] = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * vars[0];
	start_offset = 0;
	if (bounds[0] < 0)
	{
		start_offset = -bounds[0];
		vars[1] += start_offset * vars[0];
		bounds[0] = 0;
	}
	if (bounds[1] >= HEIGHT)
		bounds[1] = HEIGHT - 1;
	if (bounds[0] >= HEIGHT)
		bounds[0] = HEIGHT - 1;
	if (bounds[1] < 0)
		bounds[1] = 0;
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int		bounds[2];
	double	vars[2];
	int		y;

	if (!game->textures[ray->tex_num].img
		|| !game->textures[ray->tex_num].addr)
		return ;
	init_wall_render(game, ray, bounds, vars);
	y = bounds[0];
	while (y <= bounds[1])
	{
		put_pixel(&game->img, x, y,
			process_wall_pixel(game, ray, vars));
		y++;
	}
}
