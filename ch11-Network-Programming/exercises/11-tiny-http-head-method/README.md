# Exercise 11.11

Extend Tiny to support the HTTP HEAD method. Check your work using *Telnet* as a Web client.

## Solution

The starting point is the ending code for Practice Problem 11.10.

I updated the allowed methods and set the CGI environment variable `REQUEST_METHOD`:

```c
    if (strcasecmp(method, "GET") != 0 && strcasecmp(method, "HEAD") != 0) {  //line:netp:doit:beginrequesterr
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }                                                    //line:netp:doit:endrequesterr
	setenv("REQUEST_METHOD", method, 1);
```

Then, in the `serve_static()` method, I read this variable to decide if content should be returned:

```c
	/* Rest of code */
    sprintf(buf, "Content-type: %s\r\n\r\n", filetype);
    Rio_writen(fd, buf, strlen(buf));    //line:netp:servestatic:endserve

	if (strcasecmp("HEAD", getenv("REQUEST_METHOD")) == 0)
		return;

    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0); //line:netp:servestatic:open
	/* Rest of code */
```

Similarly, in the CGI program `adder.c`, I similarly made sure that content only given to user
if the request method was not `HEAD`:

```c
	if (strcasecmp("HEAD", getenv("REQUEST_METHOD")) != 0)
	    printf("%s", content);
```

The following are sample interactions with the server running on port 7600:

```
telnet localhost 7600
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
GET / HTTP/1.1

HTTP/1.0 200 OK
Server: Tiny Web Server
Content-length: 138
Content-type: text/html

<html>
<head><title>test</title></head>
<body>
<img align="middle" src="godzilla.gif">
Dave O'Hallaron
</body>
</html>
GET / HTTP/1.1

Connection closed by foreign host.
```

```
$ telnet localhost 7600
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
HEAD / HTTP/1.1

HTTP/1.0 200 OK
Server: Tiny Web Server
Content-length: 139
Content-type: text/html

HEAD / HTTP/1.1

Connection closed by foreign host.
```

```
$ telnet localhost 7600
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
GET /cgi-bin/adder?n1=3&n2=7 HTTP/1.1

HTTP/1.0 200 OK
Server: Tiny Web Server
Connection: close
Content-length: 124
Content-type: text/html

Welcome to add.com: Modified by SergioTHE Internet addition portal.
<p>The answer is: 3 + 7 = 10
<p>Thanks for visiting!
Connection closed by foreign host.
```

```
$ telnet localhost 7600
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
HEAD /cgi-bin/adder?n1=3&n2=7 HTTP/1.1

HTTP/1.0 200 OK
Server: Tiny Web Server
Connection: close
Content-length: 124
Content-type: text/html

Connection closed by foreign host.
```
