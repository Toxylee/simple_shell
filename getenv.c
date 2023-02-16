#include &quot;shell.h&quot;
/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
if (!info-&gt;environ || info-&gt;env_changed)
{
info-&gt;environ = list_to_strings(info-&gt;env);
info-&gt;env_changed = 0;
}
return (info-&gt;environ);
}
/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
list_t *node = info-&gt;env;
size_t i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = starts_with(node-&gt;str, var);
if (p &amp;&amp; *p == &#39;=&#39;)
{
info-&gt;env_changed = delete_node_at_index(&amp;(info-&gt;env), i);
i = 0;
node = info-&gt;env;

continue;
}
node = node-&gt;next;
i++;
}
return (info-&gt;env_changed);
}
/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;
if (!var || !value)
return (0);
buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, &quot;=&quot;);
_strcat(buf, value);
node = info-&gt;env;
while (node)
{
p = starts_with(node-&gt;str, var);
if (p &amp;&amp; *p == &#39;=&#39;)
{
free(node-&gt;str);
node-&gt;str = buf;
info-&gt;env_changed = 1;
return (0);
}
node = node-&gt;next;
}
add_node_end(&amp;(info-&gt;env), buf, 0);
free(buf);
info-&gt;env_changed = 1;
return (0);
}