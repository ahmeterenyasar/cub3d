/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:05:12 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/18 14:05:32 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_strlen_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	*ft_strjoin_split(char **split, int start)
{
	int		i;
	char	*res;
	char	*temp;

	i = start;
	res = NULL;
	while (split[i])
	{
		if (!res)
			res = ft_strdup(split[i]);
		else
		{
			temp = res;
			res = ft_strjoin(res, "");
			free(temp);
			temp = res;
			res = ft_strjoin(res, split[i]);
			free(temp);
		}
		i++;
	}
	return (res);
}

void	free_split_with_index(char **split, int i)
{
	while (split[i])
	{
		free(split[i]);
		i++;
	}
}

void	control_split_count(char **split)
{
	char	*temp;

	if (ft_strlen_split(split) > 2)
	{
		temp = ft_strjoin_split(split, 1);
		free(split[1]);
		free_split_with_index(split, 2);
		split[1] = temp;
		split[2] = NULL;
	}
}
