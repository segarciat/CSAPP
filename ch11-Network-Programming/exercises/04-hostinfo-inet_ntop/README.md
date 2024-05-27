# Exercise 11.4

The `getaddrinfo` and `getnameinfo` functions subsume the functionality of `inet_pton` and
`inet_ntop`, respectively, and they provide a higher-level abstraction that is independent
of any particular address format. To convince yourself how handy this is, write a version of
*HOSTINFO* (Figure 11.7) that uses `inet_ntop` instead of `getnameinfo` to convert each socket
address to a dotted-decimal address string.

## Solution

To use `inet_ntop`, I had to use to cast `struct sockaddr *` to `struct sockaddr_in *`, the IP socket
address structure. In doing so we've lost the protocol independence, and it certainly was messier.
