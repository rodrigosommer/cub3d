/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_effects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/12 00:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hsv_to_rgb(double h, double s, double v)
{
	double	vals[5];
	double	rgb[3];
	int		r;
	int		g;

	vals[0] = v * s;
	vals[1] = fmod(h / 60.0, 6);
	vals[2] = vals[0] * (1 - fabs(fmod(vals[1], 2) - 1));
	vals[3] = v - vals[0];
	hsv_segment_rgb(vals[1], vals[0], vals[2], rgb);
	r = clamp_rgb((int)((rgb[0] + vals[3]) * 255));
	g = clamp_rgb((int)((rgb[1] + vals[3]) * 255));
	vals[4] = (rgb[2] + vals[3]) * 255;
	return (create_color(r, g, clamp_rgb((int)vals[4])));
}

int	get_rainbow_color(double time_factor, double position_factor)
{
	double	hue;

	hue = fmod(time_factor + position_factor, 360.0);
	if (hue < 0)
		hue += 360.0;
	return (hsv_to_rgb(hue, 0.9, 0.9));
}

int	apply_rainbow_shift(int original_color, int rainbow_color, double intensity)
{
	int	orig_rgb[3];
	int	rainbow_rgb[3];
	int	result_rgb[3];

	extract_rgb(original_color, &orig_rgb[0], &orig_rgb[1], &orig_rgb[2]);
	extract_rgb(rainbow_color, &rainbow_rgb[0], &rainbow_rgb[1],
		&rainbow_rgb[2]);
	result_rgb[0] = clamp_rgb((int)(orig_rgb[0]
				* (rainbow_rgb[0] * intensity / 255.0 + (1.0 - intensity))));
	result_rgb[1] = clamp_rgb((int)(orig_rgb[1]
				* (rainbow_rgb[1] * intensity / 255.0 + (1.0 - intensity))));
	result_rgb[2] = clamp_rgb((int)(orig_rgb[2]
				* (rainbow_rgb[2] * intensity / 255.0 + (1.0 - intensity))));
	return (create_color(result_rgb[0], result_rgb[1], result_rgb[2]));
}
