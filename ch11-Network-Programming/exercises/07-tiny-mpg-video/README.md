# Exercise 11.7

Extend *Tiny* so that it serves MPG video files. Check your work using a real browser.

## Solution

The code here picks up from that in Practice Problem 11.6. I simply modified the `get_filetype()`
function so that it checks for `.mp4` in addition to the other extension types. I picked MP4 because
it is short for MPEG-4. The following is the updated code:

```c
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
	/* Here is the new content */
	else if (strstr(filename, ".mp4"))
		strcpy(filetype, "video/mp4");
    else
		strcpy(filetype, "text/plain");
}  
```

I grabbed a free clip from [Pexels](https://www.pexels.com/video/setting-up-for-a-photo-shoot-of-natural-and-organic-hygiene-products-organized-in-a-metal-basket-3755796/) and named it
`./tiny/pexels-cottonbro-studio.mp4`.

When I access http://localhost:7000/pexels-cottonbro-studio.mp4 on Firefox, the video begins playing.
