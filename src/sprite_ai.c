/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ai.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	sprite_can_see_player(t_game *game, t_sprite *sprite)
{
	double	dx;
	double	dy;
	double	dist;
	double	step_x;
	double	step_y;

	dx = game->player.x - sprite->x;
	dy = game->player.y - sprite->y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > sprite->aggro_distance)
		return (0);
	step_x = dx / (dist * 10);
	step_y = dy / (dist * 10);
	return (check_line_of_sight(game, sprite, step_x, step_y));
}

static int	check_los_steps(t_game *game, double cx, double cy, t_pos *step)
{
	int	i;

	i = 0;
	while (i < step->y)
	{
		if (check_sprite_collision(game, cx, cy))
			return (0);
		cx += step->x;
		cy += step->y;
		i++;
	}
	return (1);
}

int	check_line_of_sight(t_game *game, t_sprite *sprite, double step_x,
	double step_y)
{
	double	dx;
	double	dy;
	double	check_x;
	double	check_y;
	t_pos	step;

	(void)step_y;
	dx = game->player.x - sprite->x;
	dy = game->player.y - sprite->y;
	step.y = (int)(sqrt(dx * dx + dy * dy) * 10);
	step.x = step_x;
	check_x = sprite->x;
	check_y = sprite->y;
	return (check_los_steps(game, check_x, check_y, &step));
}

void	move_sprite_towards_player(t_game *game, t_sprite *sprite)
{
	double	dx;
	double	dy;
	double	dist;
	double	new_x;
	double	new_y;

	dx = game->player.x - sprite->x;
	dy = game->player.y - sprite->y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 0.1)
	{
		dx /= dist;
		dy /= dist;
		new_x = sprite->x + dx * sprite->move_speed;
		new_y = sprite->y + dy * sprite->move_speed;
		if (!check_sprite_collision(game, new_x, sprite->y))
			sprite->x = new_x;
		if (!check_sprite_collision(game, sprite->x, new_y))
			sprite->y = new_y;
	}
}

void	update_sprite_animation(t_sprite *sprite)
{
	double	anim_speed;

	if (sprite->is_dead)
		return ;
	if (sprite->is_aggressive && sprite->health > 100)
		anim_speed = 1.2;
	else
		anim_speed = 0.8;
	sprite->anim_timer += anim_speed;
	if (sprite->anim_timer > 0.25)
	{
		sprite->frame = 1 - sprite->frame;
		sprite->anim_timer = 0.0;
	}
}
