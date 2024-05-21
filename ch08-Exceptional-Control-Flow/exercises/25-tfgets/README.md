# Exercise 8.25

Write a version of the `fgets` function, called `tfgets`, that times out after 5 seconds.
The `tfgets` function accepts the same input as `fgets`. If the user doesn't type an input
line within 5 seconds, `tfgets` returns `NULL`. Otherwise, it returns a pointer to the
input line.
