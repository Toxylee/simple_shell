#include &quot;shell.h&quot;
/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
size_t i = 0;
while (h)
{
h = h-&gt;next;
i++;
}
return (i);
}
/**
 * list_to_strings - returns an array of strings of the list-&gt;str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t i = list_len(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node-&gt;next, i++)
{
str = malloc(_strlen(node-&gt;str) + 1);
if (!str)
{
for (j = 0; j &lt; i; j++)
free(strs[j]);
free(strs);
return (NULL);

}
str = _strcpy(str, node-&gt;str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
size_t i = 0;
while (h)
{
_puts(convert_number(h-&gt;num, 10, 0));
_putchar(&#39;:&#39;);
_putchar(&#39; &#39;);
_puts(h-&gt;str ? h-&gt;str : &quot;(nil)&quot;);
_puts(&quot;\n&quot;);
h = h-&gt;next;
i++;
}
return (i);
}
/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = starts_with(node-&gt;str, prefix);
if (p &amp;&amp; ((c == -1) || (*p == c)))
return (node);

node = node-&gt;next;
}
return (NULL);
}
/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t i = 0;
while (head)
{
if (head == node)
return (i);
head = head-&gt;next;
i++;
}
return (-1);
}