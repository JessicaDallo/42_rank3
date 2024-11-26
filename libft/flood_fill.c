/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheila <sheila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:07:39 by sheila            #+#    #+#             */
/*   Updated: 2024/07/23 12:02:49 by sheila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "flood_fill.h"

void	fill(char **tab, t_point size, int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= size.x || y >= size.y || tab[y][x] != c)
		return;
	tab[y][x] = 'F';
	fill(tab, size, x + 1, y, c);
	fill(tab, size, x - 1, y, c);
	fill(tab, size, x, y + 1, c);
	fill(tab, size, x, y - 1, c);
}  
void  flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin.x, begin.y, tab[begin.y][begin.x]);
}

char** make_area(char** zone, t_point size)
{
	char** new;

	new = malloc(sizeof(char*) * size.y);
	for (int i = 0; i < size.y; ++i)
	{
		new[i] = malloc(size.x + 1);
		for (int j = 0; j < size.x; ++j)
			new[i][j] = zone[i][j];
		new[i][size.x] = '\0';
	}

	return new;
}

/*int main(void)
{
	t_point size = {8, 5};
	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
	};

	char**  area = make_area(zone, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	t_point begin = {7, 4};
	flood_fill(area, size, begin);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	return (0);
}*/