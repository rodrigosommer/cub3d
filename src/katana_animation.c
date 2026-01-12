/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   katana_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_default_params(t_katana_p *params)
{
	params->offset_x = -100;
	params->offset_y = -50;
	params->rotation = 0.0;
	params->scale = 2.0;
}

void	apply_katana_animation(t_game *game, t_katana_p *params)
{
	double	swing_phase;
	double	animation_factor;

	init_default_params(params);
	if (game->katana_slash_active)
	{
		calculate_swing_phase(game, &swing_phase);
		apply_swing_params(params, swing_phase);
		animation_factor = game->katana_slash_timer / 0.3;
		if (animation_factor > 1.0)
			animation_factor = 1.0;
		draw_blur_effect(game, params, animation_factor);
	}
}

void	render_katana_hands(t_game *game)
{
	t_katana_p	params;

	apply_katana_animation(game, &params);
	draw_katana_with_effects(game, &params);
}
