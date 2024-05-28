# Exercise 11.6

A. Modify *Tiny* so that it echoes every request line and request header.

B. Use your favorite browser to make a request to *Tiny* for static content.
Capture the output from *Tiny* in a file.

C. Inspect the output of *Tiny* to determine the version of HTTP your browser
uses.

D. Consult the HTTP/1.1 standard in RFC 2616 to determine the meaning of each
header in the HTTP request from your browser. You can obtain RFC 2616 from
www.rfc-editor.org/rfc.html

## Solution

A. I began by making changes to ensure that `make` would run without any warnings.
Then I proceeded to changing some function definitions. First, I defined a constant for
the maximum size of a header that Tiny will accept:

```c
#define MAX_HEADERS MAXLINE
```

Then I increased the size of `buf` in the `doit()` function so that there is enough room
for both the request line and the request headers, and declared variables to track their
respective lengths:

```c
size_t requestLineSize, requestHeaderSize, requestLength;
char buf[MAXLINE + MAX_HEADERS], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
```

I began by saving the size of the request line:

```c
/* Read request line */
Rio_readinitb(&rio, fd);
if (!(requestLineSize = Rio_readlineb(&rio, buf, MAXLINE)))
    return;

/* Display request line in stdout */
printf("%s", buf);
```
Then I changed the `read_requesthdrs()` function's behavior. Before, it would just print all headers
to standard output. Now I have changed its signature to accept a buffer, to which it will write the headers.
It also returns the number of bytes written to the header. I moved the call to be after the logic that parses
the requestline:

```c
/* Read headers */
requestHeaderSize = read_requesthdrs(&rio, buf + requestLineSize, MAX_HEADERS); //line:netp:doit:readrequesthdrs
printf("%s", buf + requestLineSize);
```

Then, in the branch that serves the static resource, I wrote the request line and header after having
served the static page:

```c
requestLength = requestLineSize + requestHeaderSize;
serve_static(fd, filename, sbuf.st_size, requestLength + sbuf.st_size);        //line:netp:doit:servestatic
Rio_writen(fd, buf, requestLength);
```

Notice that I modified the `serve_static()` function to add an extra argument which I call `contentLength`.
Before, the content length was just the file's size; now, it is the file's size plus the combined size of
the request line and headers.

The following is the updated `read_requesthdrs()` routine:

```c
size_t read_requesthdrs(rio_t *rp, char *buf, size_t size)
{
    size_t bytesRead = 0, remaining = size;
    char *p = buf;
    *p = '\0';
    do {
        p = buf + bytesRead;
        bytesRead += Rio_readlineb(rp, p, remaining);
        remaining -= bytesRead;
    } while (remaining > 0 && strcmp(p, "\r\n") != 0);
    return bytesRead;
}
```

This correctly displayed the request headers in the browser for each valid request for static content.

B. I ran the server as

```bash
cd tiny
./tiny 8000
```

I copied the output into `request_line_headers.txt`.

C. Based on the output, I saw:

```
GET / HTTP/1.1
```

This suggests my browser supports HTTP version 1.1.

D. Two requests were made to the server: an initial one for the HTML file at the home URI,
for which the browser returned `./tiny/home.html`, and the image that `./tiny/home.html` links
to, namely `./tiny/godzilla.gif`.

There were several headers  sent by the client:

- `Accept-Encoding`: Restricts the content-codings that are acceptable in the response. In this case,
the client specified `gzip`, `deflate`, `br`, and `zstd`. So, for example, the server may choose to
compress the response and that would be acceptable.

- `Accept-Language`: Restricts the set of natural languages that are preferred as a response to the
request. each of which may have an associated quality value, which represents an estimate of the user's
preference for the languages specified by that range.

There are several other headers, which I'll skip.
