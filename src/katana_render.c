/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   katana_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_katana_draw(t_katana_draw *kd, t_game *game, t_katana_p *p)
{
	kd->cos_r = cos(p->rotation);
	kd->sin_r = sin(p->rotation);
	kd->width = (int)(game->katana_texture.width * p->scale);
	kd->height = (int)(game->katana_texture.height * p->scale);
	kd->start_x = WIDTH - kd->width + p->offset_x;
	kd->start_y = HEIGHT - kd->height + p->offset_y;
}

static void	calc_tex_coords(t_game *game, t_katana_draw *kd, int coords[2],
	int xy[2])
{
	int	temp_x;
	int	temp_y;

	temp_x = (int)((xy[0] - kd->start_x) * kd->cos_r
			- (xy[1] - kd->start_y) * kd->sin_r);
	temp_y = (int)((xy[0] - kd->start_x) * kd->sin_r
			+ (xy[1] - kd->start_y) * kd->cos_r);
	coords[0] = temp_x * game->katana_texture.width / kd->width;
	coords[1] = temp_y * game->katana_texture.height / kd->height;
}

static int	get_valid_color(t_game *game, t_katana_draw *kd, int x, int y)
{
	int	coords[2];
	int	xy[2];
	int	color;

	xy[0] = x;
	xy[1] = y;
	calc_tex_coords(game, kd, coords, xy);
	if (coords[0] >= 0 && coords[0] < game->katana_texture.width
		&& coords[1] >= 0 && coords[1] < game->katana_texture.height)
	{
		color = get_texture_pixel(&game->katana_texture, coords[0], coords[1]);
		if (color != 0xFFFFFF && color != 0x00FFFFFF && color != 0)
			return (color);
	}
	return (-1);
}

static void	draw_katana_pixel_loop(t_game *game, t_katana_draw *kd)
{
	int	x;
	int	y;
	int	color;

	y = kd->start_y;
	while (y < kd->start_y + kd->height && y < HEIGHT)
	{
		x = kd->start_x;
		while (x < kd->start_x + kd->width && x < WIDTH)
		{
			if (x >= 0 && y >= 0)
			{
				color = get_valid_color(game, kd, x, y);
				if (color != -1)
					put_pixel(&game->img, x, y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_katana_with_effects(t_game *game, t_katana_p *params)
{
	t_katana_draw	kd;

	init_katana_draw(&kd, game, params);
	draw_katana_pixel_loop(game, &kd);
}
