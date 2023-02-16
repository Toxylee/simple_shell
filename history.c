#include &quot;shell.h&quot;
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *get_history_file(info_t *info)
{
char *buf, *dir;

dir = _getenv(info, &quot;HOME=&quot;);
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, &quot;/&quot;);
_strcat(buf, HIST_FILE);
return (buf);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
ssize_t fd;
char *filename = get_history_file(info);
list_t *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info-&gt;history; node; node = node-&gt;next)
{
_putsfd(node-&gt;str, fd);
_putfd(&#39;\n&#39;, fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{

int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(info);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &amp;st))
fsize = st.st_size;
if (fsize &lt; 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen &lt;= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i &lt; fsize; i++)
if (buf[i] == &#39;\n&#39;)
{
buf[i] = 0;
build_history_list(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
build_history_list(info, buf + last, linecount++);
free(buf);
info-&gt;histcount = linecount;
while (info-&gt;histcount-- &gt;= HIST_MAX)
delete_node_at_index(&amp;(info-&gt;history), 0);
renumber_history(info);
return (info-&gt;histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)

{
list_t *node = NULL;
if (info-&gt;history)
node = info-&gt;history;
add_node_end(&amp;node, buf, linecount);
if (!info-&gt;history)
info-&gt;history = node;
return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
list_t *node = info-&gt;history;
int i = 0;
while (node)
{
node-&gt;num = i++;
node = node-&gt;next;
}
return (info-&gt;histcount = i);
}
