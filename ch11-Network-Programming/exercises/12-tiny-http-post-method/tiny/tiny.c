/* $begin tinymain */
/*
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the 
 *     GET method to serve static and dynamic content.
 *
 * Updated 11/2019 droh 
 *   - Fixed sprintf() aliasing issue in serve_static(), and clienterror().
 */
#include "csapp.h"

#define MAX_HEADERS MAXLINE

void doit(int fd);
size_t read_requesthdrs(rio_t *rp, char *buf, size_t size);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize, size_t contentLength);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);
void sigchldHandler(int sig);

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
    }

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
}
/* $end tinymain */

/*
 * doit - handle one HTTP request/response transaction
 */
/* $begin doit */
void doit(int fd) 
{
    int is_static;
    struct stat sbuf;
	size_t requestLineSize, requestHeaderSize, requestLength;
    char buf[MAXLINE + MAX_HEADERS], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    /* Read request line */
    Rio_readinitb(&rio, fd);
	if (!(requestLineSize = Rio_readlineb(&rio, buf, MAXLINE)))  //line:netp:doit:readrequest
    	return;
	
	/* Display request line in stdout */
    printf("%s", buf);

	/* Parse request line */
    sscanf(buf, "%s %s %s", method, uri, version);       //line:netp:doit:parserequest
    if (strcasecmp(method, "GET") != 0
		&& strcasecmp(method, "HEAD") != 0
		&& strcasecmp(method, "POST") != 0) {  //line:netp:doit:beginrequesterr
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }                                                    //line:netp:doit:endrequesterr
	setenv("REQUEST_METHOD", method, 1);

	/* Read headers */
    requestHeaderSize = read_requesthdrs(&rio, buf + requestLineSize, MAX_HEADERS); //line:netp:doit:readrequesthdrs
	printf("%s", buf + requestLineSize);

    /* Parse URI from GET request */
    is_static = parse_uri(uri, filename, cgiargs);       //line:netp:doit:staticcheck
    if (stat(filename, &sbuf) < 0) {                     //line:netp:doit:beginnotfound
		clienterror(fd, filename, "404", "Not found",
				"Tiny couldn't find this file");
		return;
    }                                                    //line:netp:doit:endnotfound

    if (is_static) { /* Serve static content */          
		if (strcasecmp("POST", method) == 0) {
			clienterror(fd, method, "501", "Not Implemented",
				"Tiny does not implement this method for this path");
			return;
		}
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) { //line:netp:doit:readable
			clienterror(fd, filename, "403", "Forbidden",
				"Tiny couldn't read the file");
			return;
		}
		requestLength = requestLineSize + requestHeaderSize;
		serve_static(fd, filename, sbuf.st_size, requestLength + sbuf.st_size);        //line:netp:doit:servestatic
		Rio_writen(fd, buf, requestLength);
    }
    else { /* Serve dynamic content */
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) { //line:netp:doit:executable
			clienterror(fd, filename, "403", "Forbidden",
				"Tiny couldn't run the CGI program");
			return;
		}
		serve_dynamic(fd, filename, cgiargs);            //line:netp:doit:servedynamic
    }
}
/* $end doit */

/*
 * read_requesthdrs - read HTTP request headers
 */
/* $begin read_requesthdrs */
size_t read_requesthdrs(rio_t *rp, char *buf, size_t size) 
{
	size_t bytesRead = 0, remaining = size;
	char *p = buf;
	do {
		p = buf + bytesRead;
		bytesRead += Rio_readlineb(rp, p, remaining);
		remaining -= bytesRead;
	} while (remaining > 0 && strcmp(p, "\r\n") != 0);
    return bytesRead;
}
/* $end read_requesthdrs */

/*
 * parse_uri - parse URI into filename and CGI args
 *             return 0 if dynamic content, 1 if static
 */
/* $begin parse_uri */
int parse_uri(char *uri, char *filename, char *cgiargs) 
{
    char *ptr;

    if (!strstr(uri, "cgi-bin")) {  /* Static content */ //line:netp:parseuri:isstatic
		strcpy(cgiargs, "");                             //line:netp:parseuri:clearcgi
		strcpy(filename, ".");                           //line:netp:parseuri:beginconvert1
		strcat(filename, uri);                           //line:netp:parseuri:endconvert1
		if (uri[strlen(uri)-1] == '/')                   //line:netp:parseuri:slashcheck
			strcat(filename, "home.html");               //line:netp:parseuri:appenddefault
		return 1;
	} else {  /* Dynamic content */                        //line:netp:parseuri:isdynamic
		ptr = index(uri, '?');                           //line:netp:parseuri:beginextract
		if (ptr) {
			strcpy(cgiargs, ptr+1);
			*ptr = '\0';
		}
		else 
			strcpy(cgiargs, "");                         //line:netp:parseuri:endextract
		strcpy(filename, ".");                           //line:netp:parseuri:beginconvert2
		strcat(filename, uri);                           //line:netp:parseuri:endconvert2
		return 0;
    }
}
/* $end parse_uri */

/*
 * serve_static - copy a file back to the client 
 */
/* $begin serve_static */
void serve_static(int fd, char *filename, int filesize, size_t contentLength)
{
    int srcfd;
	size_t bytesRead;
    char *srcp, filetype[MAXLINE], buf[MAXBUF + MAXLINE];

    /* Send response headers to client */
    get_filetype(filename, filetype);    //line:netp:servestatic:getfiletype
    sprintf(buf, "HTTP/1.0 200 OK\r\n"); //line:netp:servestatic:beginserve
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %ld\r\n", contentLength);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: %s\r\n\r\n", filetype);
    Rio_writen(fd, buf, strlen(buf));    //line:netp:servestatic:endserve

	if (strcasecmp("HEAD", getenv("REQUEST_METHOD")) == 0)
		return;

    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0); //line:netp:servestatic:open
    srcp = Malloc(filesize + 1);        /* Additional byte for null byte */
    if ((bytesRead = rio_readn(srcfd, srcp, filesize)) == -1 || write(fd, srcp, bytesRead) == -1) {
        Free(srcp);
        clienterror(fd, "GET", "500", "Internal Server Error",
                    "Tiny does not implement this method");
        return;
    }   
    Close(srcfd);                       //line:netp:servestatic:close
    Free(srcp);
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) 
{
    if (strstr(filename, ".html"))
		strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
		strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
		strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
		strcpy(filetype, "image/jpeg");
	else if (strstr(filename, ".mp4"))
		strcpy(filetype, "video/mp4");
    else
		strcpy(filetype, "text/plain");
}  
/* $end serve_static */

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
/* $begin serve_dynamic */
void serve_dynamic(int fd, char *filename, char *cgiargs) 
{
    char buf[MAXLINE], *emptylist[] = { NULL };

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n"); 
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));
 
    if (Fork() == 0) { /* Child */ //line:netp:servedynamic:fork
        /* Real server would set all CGI vars here */
        setenv("QUERY_STRING", cgiargs, 1); //line:netp:servedynamic:setenv
        Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */ //line:netp:servedynamic:dup2
        Execve(filename, emptylist, environ); /* Run CGI program */ //line:netp:servedynamic:execve
    }
}
/* $end serve_dynamic */

/*
 * clienterror - returns an error message to the client
 */
/* $begin clienterror */
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE];

    /* Print the HTTP response headers */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n\r\n");
    Rio_writen(fd, buf, strlen(buf));

    /* Print the HTTP response body */
    sprintf(buf, "<html><title>Tiny Error</title>");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<body bgcolor=""ffffff"">\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
    Rio_writen(fd, buf, strlen(buf));
}
/* $end clienterror */

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