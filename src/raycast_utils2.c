/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/12 00:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_wall_pixel(t_game *game, t_ray *ray, double *vars,
	int rainbow_color)
{
	int	color;

	color = get_texture_pixel(&game->textures[ray->tex_num], ray->tex_x,
			get_safe_tex_y(vars[1], game->textures[ray->tex_num].height));
	vars[1] += vars[0];
	if (game->rainbow_enabled)
		color = apply_rainbow_shift(color, rainbow_color,
				game->rainbow_intensity);
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

int	get_safe_tex_y(double tex_pos, int tex_height)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_height)
		tex_y = tex_height - 1;
	return (tex_y);
}
