NAME		= cub3D

SRCDIR		= src
INCDIR		= inc
OBJDIR		= obj

SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/parse.c \
			  $(SRCDIR)/parse_map.c \
			  $(SRCDIR)/parse_textures.c \
			  $(SRCDIR)/parse_colors.c \
			  $(SRCDIR)/validate.c \
			  $(SRCDIR)/validate_utils.c \
			  $(SRCDIR)/init.c \
			  $(SRCDIR)/render.c \
			  $(SRCDIR)/raycasting.c \
			  $(SRCDIR)/raycast_utils.c \
			  $(SRCDIR)/raycast_utils2.c \
			  $(SRCDIR)/events.c \
			  $(SRCDIR)/key_pres.c \
			  $(SRCDIR)/movement.c \
			  $(SRCDIR)/texture.c \
			  $(SRCDIR)/cleanup.c \
			  $(SRCDIR)/free_get_texture.c \
			  $(SRCDIR)/parse_map_utils.c \
			  $(SRCDIR)/parse_map_utils2.c \
			  $(SRCDIR)/parse_map_validation.c \
			  $(SRCDIR)/parse_map_enemy_bonus.c \
			  $(SRCDIR)/parse_colors_utils.c \
			  $(SRCDIR)/utils.c \
			  $(SRCDIR)/utils2.c \
			  $(SRCDIR)/minimap.c \
			  $(SRCDIR)/minimap_utils.c \
			  $(SRCDIR)/mouse.c \
			  $(SRCDIR)/sprites.c \
			  $(SRCDIR)/sprite_init.c \
			  $(SRCDIR)/sprite_init2.c \
			  $(SRCDIR)/sprite_render.c \
			  $(SRCDIR)/sprite_draw.c \
			  $(SRCDIR)/sprite_utils.c \
			  $(SRCDIR)/sprite_textures.c \
			  $(SRCDIR)/sprite_collision.c \
			  $(SRCDIR)/sprite_ai.c \
			  $(SRCDIR)/sprite_patrol.c \
			  $(SRCDIR)/doors.c \
			  $(SRCDIR)/door_utils.c \
			  $(SRCDIR)/door_animation.c \
			  $(SRCDIR)/door_textures.c \
			  $(SRCDIR)/door_render.c \
			  $(SRCDIR)/smooth_movement.c \
			  $(SRCDIR)/game_loop.c \
			  $(SRCDIR)/katana.c \
			  $(SRCDIR)/katana_render.c \
			  $(SRCDIR)/katana_animation.c \
			  $(SRCDIR)/katana_swing.c \
			  $(SRCDIR)/katana_slash.c \
			  $(SRCDIR)/katana_door.c

OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I$(INCDIR) -Ilibft -Iminilibx-linux
LIBS		= -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C minilibx-linux
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C libft clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
