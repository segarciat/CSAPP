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

A. My understanding is that by echo every request line and request header, the
exercise means to echo to standard out, not to serve it as part of the static
and dynamic content. The program already does that, so no change was necessary.
I did make some changes to address some compile-time warning that were output
when running `make`.

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
