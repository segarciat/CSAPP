# Exercise 11.8

Modify *Tiny* so that it reaps CGI children inside a SIGCHLD handler instead of explicitly
waiting for them to terminate.


## Solution

The starting point is the ending code for Practice Problem 11.7. I implemented the following
`SIGCHLD` handler:

```c
/* Reap CGI children */
void sigchldHandler(int sig)
{
	int savedErrno = errno;
	while (waitpid(-1, NULL, 0) > 0) {
		Sio_puts("Handler reaped CGI child\n");
	}
	if (errno != ECHILD)
		Sio_error("waitpid error");
	errno = savedErrno;
}
```

This is precisely like the one given in Figure 8.37, page 773. Then prior to the main loop,
I installed it:

```c
	/* Set up SIGCHLD handler */
	Signal(SIGCHLD, sigchldHandler);

    listenfd = Open_listenfd(argv[1]);
    while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:netp:tiny:accept
			Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
						port, MAXLINE, 0);
			printf("Accepted connection from (%s, %s)\n", hostname, port);
		doit(connfd);                                             //line:netp:tiny:doit
		Close(connfd);                                            //line:netp:tiny:close
    }
```

Finally, I removed the `Wait()` would make the main thread hang while the CGI child serviced
the request:

```c
    if (Fork() == 0) { /* Child */ //line:netp:servedynamic:fork
		/* Real server would set all CGI vars here */
		setenv("QUERY_STRING", cgiargs, 1); //line:netp:servedynamic:setenv
		Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */ //line:netp:servedynamic:dup2
		Execve(filename, emptylist, environ); /* Run CGI program */ //line:netp:servedynamic:execve
    }
	/* Removed Wait(NULL) that was here 8/
```

Even though they main loop calls `Close(connfd)`, the CGI child, having inherited the descriptor,
still has a handle on it, and therefore the connection is not quite closed until the CGI child
exits.
