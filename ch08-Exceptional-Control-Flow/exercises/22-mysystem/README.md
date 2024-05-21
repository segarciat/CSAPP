# Exercise 8.22

Write your own version of the Unix `system` function

```c
int mysystem(char *command);
```

The `mysystem` function executes `command` by invoking `/bin/sh -c command`, and then
returns after `command` has completed. If `command` exits normally (by calling the
`exit` function or executing a `return` statement), then `mysystem` returns the `command`
exit status. For example, if `command` terminats by calling `exit(8)`, then `mysystem`
returns the value 8. Otherwise, if `command` terminates abnormally, then mysystem returns
the status returned by the shell.
