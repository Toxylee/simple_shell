#include &quot;shell.h&quot;
/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
info-&gt;arg = NULL;
info-&gt;argv = NULL;
info-&gt;path = NULL;
info-&gt;argc = 0;
}
/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
int i = 0;
info-&gt;fname = av[0];
if (info-&gt;arg)
{
info-&gt;argv = strtow(info-&gt;arg, &quot; \t&quot;);
if (!info-&gt;argv)
{
info-&gt;argv = malloc(sizeof(char *) * 2);
if (info-&gt;argv)
{
info-&gt;argv[0] = _strdup(info-&gt;arg);
info-&gt;argv[1] = NULL;
}
}
for (i = 0; info-&gt;argv &amp;&amp; info-&gt;argv[i]; i++)
;
info-&gt;argc = i;
replace_alias(info);
replace_vars(info);
}

}
/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
ffree(info-&gt;argv);
info-&gt;argv = NULL;
info-&gt;path = NULL;
if (all)
{
if (!info-&gt;cmd_buf)
free(info-&gt;arg);
if (info-&gt;env)
free_list(&amp;(info-&gt;env));
if (info-&gt;history)
free_list(&amp;(info-&gt;history));
if (info-&gt;alias)
free_list(&amp;(info-&gt;alias));
ffree(info-&gt;environ);
info-&gt;environ = NULL;
bfree((void **)info-&gt;cmd_buf);
if (info-&gt;readfd &gt; 2)
close(info-&gt;readfd);
_putchar(BUF_FLUSH);
}
}