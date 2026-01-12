/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_effects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/12 00:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extract_rgb(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

int	clamp_rgb(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

static void	hsv_segment_1_2(double h_prime, double c, double x,
	double *rgb_out)
{
	if (h_prime < 1)
	{
		rgb_out[0] = c;
		rgb_out[1] = x;
		rgb_out[2] = 0;
	}
	else
	{
		rgb_out[0] = x;
		rgb_out[1] = c;
		rgb_out[2] = 0;
	}
}

static void	hsv_segment_3_4(double h_prime, double c, double x,
	double *rgb_out)
{
	if (h_prime < 4)
	{
		rgb_out[0] = 0;
		rgb_out[1] = x;
		rgb_out[2] = c;
	}
	else
	{
		rgb_out[0] = 0;
		rgb_out[1] = c;
		rgb_out[2] = x;
	}
}

void	hsv_segment_rgb(double h_prime, double c, double x, double *rgb_out)
{
	if (h_prime < 2)
		hsv_segment_1_2(h_prime, c, x, rgb_out);
	else if (h_prime < 3)
	{
		rgb_out[0] = 0;
		rgb_out[1] = c;
		rgb_out[2] = x;
	}
	else if (h_prime < 5)
		hsv_segment_3_4(h_prime, c, x, rgb_out);
	else
	{
		rgb_out[0] = c;
		rgb_out[1] = 0;
		rgb_out[2] = x;
	}
}
