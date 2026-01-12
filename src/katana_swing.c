/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   katana_swing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_swing_phase(t_game *game, double *swing)
{
	double	animation_factor;

	animation_factor = game->katana_slash_timer / 0.8;
	if (animation_factor > 1.0)
		animation_factor = 1.0;
	*swing = sin(animation_factor * 3.14159 * 1.5);
}

void	apply_swing_params(t_katana_p *params, double swing)
{
	params->offset_x = -50 + (int)(80.0 * swing);
	params->offset_y = -30 + (int)(-40.0 * swing);
	params->rotation = -0.5 + (1.2 * swing);
	params->scale = 1.2 + (0.3 * swing);
}

void	draw_blur_effect(t_game *game, t_katana_p *p, double anim_f)
{
	int			blur_effect;
	int			i;
	t_katana_p	blur_p;

	if (anim_f > 0.7)
	{
		blur_effect = (int)((anim_f - 0.7) * 10);
		i = 0;
		while (i < blur_effect)
		{
			blur_p.offset_x = p->offset_x + i * 5;
			blur_p.offset_y = p->offset_y + i * 2;
			blur_p.rotation = p->rotation + i * 0.1;
			blur_p.scale = p->scale * (1.0 - i * 0.05);
			draw_katana_with_effects(game, &blur_p);
			i++;
		}
	}
}
