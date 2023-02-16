#include &quot;shell.h&quot;
/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
if (ptr &amp;&amp; *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);

}