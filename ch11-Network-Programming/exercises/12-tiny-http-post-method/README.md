# Exercise 11.12

Extend *Tiny* so that it serves dynamic content requested by the HTTP POST method. Check your
work using your favorite web browser.

## Solution

The starting point is the ending code for Practice Problem 11.11.

It was unclear from the exercise whether I should handle HTTP POST requests by reading the
request body and parse the arguments that way. Similarly, it was unclear to me whether
I should return data to the client in a format such as JSON, as is usually done in web development.

Instead, I simply allowed POST for the dynamic route, and expected the client to provide the
arguments in the query parameters like with GET. In other words, GET and POST are equivalent
when invoked in `/cgi-bin/adder`.

Instead of the browser, I used `curl`:

```
$ curl -X POST "http://localhost:7600/cgi-bin/adder?n1=2&n2=3"
Welcome to add.com: Modified by SergioTHE Internet addition portal.
<p>The answer is: 2 + 3 = 5
<p>Thanks for visiting!
$
```
