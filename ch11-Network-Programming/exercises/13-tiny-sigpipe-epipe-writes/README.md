# Exercise 11.13

Modify *Tiny* sot hat it deals cleanly (without terminating) with the `SIGPIPE` signals and
`EPIPE` errors that occur when the `write` function attempts to write to a prematurely closed
connection.

## Solution

The starting point is the ending code for Practice Problem 11.12.

As discussed in the Aside on page 964, if a server writes to a connection that has already been
closed by the client, then the first write returns normally, but the second one causes the delivery
of a `SIGPIPE` signal whose default behavior is to terminate the process. If the `SIGPIPE`
signal is caught or ignored, then the second write operation returns `-1` (instaed of causing the
delivery of `SIGPIPE`), with `errno` set to `EPIPE`.

In order to simulate this scenario, I added a call to `sleep()` to allow me enough time to close
the browser tab before the server has a chance to write:

```c
	/* More code */
	Sleep(3);
    if (is_static) { /* Serve static content */          
		if (strcasecmp("POST", method) == 0) {
			clienterror(fd, method, "501", "Not Implemented",
	} else { /* serve_dynamic */}
```

I indeed saw that the server was terminated in this case.

To address the issue, I began by changing the disposition for `SIGPIPE` to ignore:

```c
	/* More code */
    Signal(SIGCHLD, sigchldHandler);	/* Handler to reap children */
    Signal(SIGPIPE, SIG_IGN);			/* Ignore SIGPIPE to stay running after prematurely closed connections */
	/* More code */
```

The server uses `Rio_writen` to write to the connection descriptor. It calls `rio_writen()`, which
in turn calls `write()`. When `write()` returns `-1`, it passes it up to `rio_write()`, which
in turn passes it up to `Rio_writen()`. However, this last function calls `unix_error()`, which
terminates the process.

Therefore, I replaced all calls to `Rio_writen()` with calls to `rio_write_epipe()`, which is
a wrapper for `rio_writen()` that I defined, and is given below:

```c
void rio_writen_epipe(int fd, void *usrbuf, size_t n)
{
	if (rio_writen(fd, usrbuf, n) == -1 && errno != EPIPE)
		unix_error("rio_writen_epipe");
}
```

When it returns `-1` and `errno` is `EPIPE`, the error is ignored. I verified that the server
did not terminate as a result of closing the browser early.
