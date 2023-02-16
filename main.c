#include &quot;shell.h&quot;
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };
int fd = 2;
asm (&quot;mov %1, %0\n\t&quot;
&quot;add $3, %0&quot;
: &quot;=r&quot; (fd)
: &quot;r&quot; (fd));

if (ac == 2)
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(&quot;: 0: Can&#39;t open &quot;);
_eputs(av[1]);
_eputchar(&#39;\n&#39;);
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info-&gt;readfd = fd;
}
populate_env_list(info);
read_history(info);
hsh(info, av);
return (EXIT_SUCCESS);
}