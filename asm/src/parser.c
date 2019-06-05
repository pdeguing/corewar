#include <assembler.h>

/*
** Verifies that the filename is valid with .s extension.
*/

t_error		verifyFilename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len <= 3)
		return ft_strdup("file name too short");
	if (filename[len - 1] != 's' || filename[len - 2] != '.')
		return ft_strdup("incorrect file extension");
	return NULL;
}

/*
** Fills the champ struct with the content of file described by fd.
*/
t_error		fillChamp(t_champ *champ, int fd)
{
	t_error		err;

	err = getName(&champ->name, fd);
	if (err)
		return err;
	err = getComment(&champ->comment, fd);
	if (err)
		return err;
	err = getContent(&champ->content, fd);
	if (err)
		return err;
	return NULL;
}

/*
** Parses the file into a t_champ struct, does various verifications of input
** and returns err in case of error.
*/

t_error			parser(t_champ *champ, char *filename)
{
	int			fd;
	t_error		err;

	err = verifyFilename(filename);
	if (err)
		return (err);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ft_strdup(strerror(errno));
	champ->fname = ft_strsub(filename, 0, ft_strlen(filename) - 2);
	err = fillChamp(champ, fd);
	close(fd);
	if (err)
		return (err);
	return NULL;
}
