/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"

# define WIDTH 1024
# define HEIGHT 768
# define FOV 66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define TILE_SIZE 1.0

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_SPACE 32
# define KEY_E 101
# define KEY_R 114
# define KEY_ENTER 65293

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define MINIMAP_SIZE 150
# define MINIMAP_SCALE 5
# define MINIMAP_X 20
# define MINIMAP_Y 20

# define MAX_SPRITES 10

# define DOOR_CLOSED 0
# define DOOR_OPENING 1
# define DOOR_OPEN 2
# define DOOR_CLOSING 3

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	pitch;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_num;
}	t_ray;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	vel_x;
	double	vel_y;
	double	target_x;
	double	target_y;
	int		texture_id;
	int		frame;
	double	anim_timer;
	double	move_timer;
	int		is_aggressive;
	double	aggro_distance;
	double	move_speed;
	int		health;
	int		is_split;
	double	split_timer;
	int		slices_received;
	int		is_dead;
}	t_sprite;

typedef struct s_door
{
	int		x;
	int		y;
	int		state;
	double	animation_timer;
	double	animation_progress;
	int		orientation;
}	t_door;

typedef struct s_katana_p
{
	int		offset_x;
	int		offset_y;
	double	rotation;
	double	scale;
}	t_katana_p;

typedef struct s_katana_draw
{
	int		start_x;
	int		start_y;
	int		width;
	int		height;
	double	cos_r;
	double	sin_r;
}	t_katana_draw;

typedef struct s_sprite_draw
{
	int		start_y;
	int		end_y;
	int		tex_x;
	int		tex_id;
	int		screen_x;
	double	dist;
}	t_sprite_draw;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		textures[4];
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	int			floor_color;
	int			ceiling_color;
	char		*texture_paths[4];
	t_sprite	sprites[MAX_SPRITES];
	int			num_sprites;
	t_img		sprite_textures[6];
	t_img		door_closed_texture;
	t_img		door_open_texture;
	t_img		floor_texture;
	t_img		ceiling_texture;
	t_img		katana_texture;
	int			katana_slash_active;
	double		katana_slash_timer;
	int			keys[65536];
	double		zbuffer[WIDTH];
	t_door		doors[50];
	int			num_doors;
	double		game_time;
	int			rainbow_enabled;
	double		rainbow_speed;
	double		rainbow_intensity;
	double		rainbow_position_factor;
	double		tombstone_x;
	double		tombstone_y;
	int			has_tombstone;
	int			level_completed;
	int			victory_reason;
}	t_game;

void	init_sprite(t_game *game, int x, int y);
int		parse_file(char *filename, t_game *game);
int		parse_textures(char *line, t_game *game);
int		parse_colors(char *line, t_game *game);
int		parse_map(int fd, t_game *game);
int		validate_map(t_game *game);
int		is_border_position(int x, int y, t_game *game);
int		check_position(int x, int y, t_game *game);
int		player_exists(t_game *game);
int		expand_map_capacity(char ***temp_map, int *capacity);
void	cleanup_map_on_error(char **temp_map, int y);
void	set_north_direction(t_game *game);
void	set_south_direction(t_game *game);
int		handle_player_char(char c, int *player_found, char *player_dir);
int		finalize_map(t_game *game, char **temp_map, int y);
int		read_map_lines(int fd, t_game *game, char ***temp_map, int *capacity);
int		process_map_line(char *line, t_game *game, int y);
void	process_special_char(char *line, t_game *game, int *x, int y);
int		parse_number(char **str);
int		create_color(int r, int g, int b);
int		parse_rgb_values(char *line, int *color);
int		init_game(t_game *game);
int		render_frame(t_game *game);
void	raycasting(t_game *game);
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double angle);
void	load_texture(t_game *game, int index, char *path);
void	cleanup_game(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_texture_pixel(t_img *texture, int x, int y);
void	error_exit(char *message);
char	*get_next_line(int fd);
void	calculate_texture(t_ray *ray, t_game *game);
void	draw_wall_column(t_game *game, t_ray *ray, int x);
int		process_wall_pixel(t_game *game, t_ray *ray, double *vars,
			int rainbow_color);
int		get_safe_tex_y(double tex_pos, int tex_height);
void	render_minimap(t_game *game);
void	draw_minimap_pixel(t_game *game, int x, int y, int color);
void	draw_minimap_border(t_game *game);
void	draw_minimap_background(t_game *game);
int		mouse_move(int x, int y, t_game *game);
void	init_sprites(t_game *game);
void	update_sprites(t_game *game);
void	render_sprites(t_game *game);
int		load_sprite_textures(t_game *game);
int		load_door_textures(t_game *game);
void	calc_sprite_screen_pos(t_game *game, t_sprite *sprite,
			int *x, double *size);
void	draw_sprite_column(t_game *game, t_sprite *sprite, int x, int size);
void	calc_sprite_bounds(int *start_x, int *end_x,
			int sprite_screen_x, double sprite_size);
int		ft_abs(int n);
void	handle_door_interaction(t_game *game);
int		key_press_smooth(int keycode, t_game *game);
int		key_release_smooth(int keycode, t_game *game);
void	process_movement(t_game *game);
int		game_loop(t_game *game);
void	init_keys(t_game *game);
void	draw_door_column(t_game *game, t_ray *ray, int x);
void	init_doors(t_game *game);
void	update_doors(t_game *game);
int		is_door_open(t_game *game, int x, int y);
t_door	*find_door(t_game *game, int x, int y);
void	update_sprite_ai(t_game *game, t_sprite *sprite);
int		check_sprite_collision(t_game *game, double x, double y);
void	move_sprite_towards_player(t_game *game, t_sprite *sprite);
int		sprite_can_see_player(t_game *game, t_sprite *sprite);
int		check_line_of_sight(t_game *game, t_sprite *sprite, double step_x,
			double step_y);
void	aggressive_patrol_behavior(t_game *game, t_sprite *sprite);
void	update_sprite_animation(t_sprite *sprite);
void	render_katana_hands(t_game *game);
int		load_katana_texture(t_game *game);
void	handle_katana_slash(t_game *game);
void	draw_katana_with_effects(t_game *game, t_katana_p *params);
void	apply_katana_animation(t_game *game, t_katana_p *params);
void	damage_sprites(t_game *game);
t_door	*find_facing_door_katana(t_game *game);
void	init_aggressive_dog(t_sprite *sprite, double x, double y,
			double aggro_dist);
void	init_berserker_dog(t_sprite *sprite, double x, double y);
void	init_samurai_crocodile(t_sprite *sprite, double x, double y);
void	init_muscular_belgian_dog(t_sprite *sprite, double x, double y);
void	init_armored_samurai(t_sprite *sprite, double x, double y);
void	init_default_params(t_katana_p *params);
void	calculate_swing_phase(t_game *game, double *swing);
void	apply_swing_params(t_katana_p *params, double swing);
void	draw_blur_effect(t_game *game, t_katana_p *p, double anim_f);
void	toggle_door(t_door *door);
int		is_valid_char(char c);
void	add_enemy_near_player(char **map, int height, int width);
int		is_door_solid(t_game *game, int x, int y);
int		hsv_to_rgb(double h, double s, double v);
int		get_rainbow_color(double time_factor, double position_factor);
int		apply_rainbow_shift(int original_color, int rainbow_color,
			double intensity);
void	extract_rgb(int color, int *r, int *g, int *b);
int		clamp_rgb(int value);
void	hsv_segment_rgb(double h_prime, double c, double x, double *rgb_out);
void	check_victory_conditions(t_game *game);
void	render_victory_screen(t_game *game);
void	init_tombstone_sprite(t_game *game);

#endif
