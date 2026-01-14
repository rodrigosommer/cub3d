/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_floor_color(char *line, t_game *game)
{
	if (game->floor_color != -1)
	{
		error_exit_with_cleanup(game, "Duplicate floor color definition");
		return (0);
	}
	if (!parse_rgb_values(line, &game->floor_color))
	{
		error_exit_with_cleanup(game, "Invalid floor color format");
		return (0);
	}
	return (1);
}

static int	handle_ceiling_color(char *line, t_game *game)
{
	if (game->ceiling_color != -1)
	{
		error_exit_with_cleanup(game, "Duplicate ceiling color definition");
		return (0);
	}
	if (!parse_rgb_values(line, &game->ceiling_color))
	{
		error_exit_with_cleanup(game, "Invalid ceiling color format");
		return (0);
	}
	return (1);
}

int	parse_colors(char *line, t_game *game)
{
	if (line[0] == 'F')
		return (handle_floor_color(line, game));
	else if (line[0] == 'C')
		return (handle_ceiling_color(line, game));
	return (0);
}
