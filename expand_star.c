#include "minishell.h"

static t_list	*ft_list_files(char *dir)
{
	DIR			*dir_stream;
	t_dirent	*dir_entry;
	t_list		*filenames;

	filenames = NULL;
	dir_stream = opendir(dir);
	while (1)
	{
		dir_entry = readdir(dir_stream);
		if (dir_entry == NULL)
			break;
		ft_lstadd_back(&filenames, ft_lstnew(ft_strdup(dir_entry->d_name)));
	}
	return (filenames);
}

static int	ft_cmp_char(char *str, char c)
{
	if (ft_strchr(str, c) == NULL)
		return (0);
	return (1);
}

char	**ft_expand_star(char *search, char *dir)
{
	char	**segments;
	t_list 	*filenames;
	char	filtered_filenames;
	int		i;

	segments = ft_split(search, '*');
	filenames = ft_list_files(dir);
	while (*segments)
	{
		i = -1;
		while (*segments[++i])
			ft_list_remove_if(&filenames, &(*segments[i]), ft_cmp_char, ft_lstdelone);
		*segments++;
	}
	filtered_filenames = ft_lst_to_arr(filenames);
	ft_lstclear(&filenames, ft_lstdelone);
	return (filtered_filenames);
}
