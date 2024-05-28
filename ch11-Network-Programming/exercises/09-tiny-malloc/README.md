# Exercise 11.9

Modify *Tiny* so that when it serves static content, it copies the request file to the connected
descriptor using `malloc`, `rio_readn`, and `rio_writen`, instead of `mmap` and `rio_writen`.

## Solution

The starting point is the ending code for Practice Problem 11.8.

I modified the `serve_static()` function so that the tail end of the function has the following code:

```c
    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0); //line:netp:servestatic:open
	srcp = Malloc(filesize + 1);		/* Additional byte for null byte */
	if ((bytesRead = rio_readn(srcfd, srcp, filesize)) == -1 || write(fd, srcp, bytesRead) == -1) {
		Free(srcp);
        clienterror(fd, "GET", "500", "Internal Server Error",
                    "Tiny does not implement this method");
		return;
	}
    Close(srcfd);                       //line:netp:servestatic:close
	Free(srcp);
```

The memory mapping approach assigns a virtual memory segment that is large enough for the file, so I
decided to have malloc allocate a buffer that is large enough for the file as well using the received
filesize argument value. In general, it's important to be careful of this approach because if the file
is very large, then we risk running out of memory if we write all data at once.
