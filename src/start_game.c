/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:30:53 by smiranda          #+#    #+#             */
/*   Updated: 2024/10/25 17:03:44 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tex_check(t_game *game)
{
	if (!game->map.n_texture || !game->map.s_texture || !game->map.w_texture
		|| !game->map.e_texture)
		return (0); // tbd with sister
	return (1);
}

static int	init_texture(t_game *game)
{
	game->tex = safe_malloc(sizeof(t_tex));
	if (!tex_check(game))
	{
		free(game->tex);
		return (0);
	}
	if (game->map.n_texture)
		game->tex->no = mlx_load_png(game->map.n_texture);
	if (game->map.s_texture)
		game->tex->so = mlx_load_png(game->map.s_texture);
	if (game->map.w_texture)
		game->tex->we = mlx_load_png(game->map.w_texture);
	if (game->map.e_texture)
		game->tex->ea = mlx_load_png(game->map.e_texture);
	if (!game->tex->no || !game->tex->so || !game->tex->we || !game->tex->ea)
	{
		free(game->tex->no);
		free(game->tex->so);
		free(game->tex->we);
		free(game->tex->ea);
		free(game->tex);
		return (0);
	}
	return (1);
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!game->mlx)
		print_error("Failed to initialize mlx.\n");
	if (!init_texture(game))
		print_error("Failed to initialize textures.\n");
	mlx_key_hook(game->mlx, key_handler, game);
	mlx_loop_hook(game->mlx, display_update, game);
	mlx_loop(game->mlx);
	// ft_exit(game); //to do
}
