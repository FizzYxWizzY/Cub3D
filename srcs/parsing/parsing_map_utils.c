/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:56:22 by mflury            #+#    #+#             */
/*   Updated: 2024/08/13 04:44:09 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// verify that the map is only composed of valid char (0,1,N,S,E,W)
// make a copy of the map.
// find the starting position for the floodfill (player starting pos).
// floodfill the map (stops if it encounter a '1', write '1' on checked index, error if it reach a ' ').
// delete the map copy

