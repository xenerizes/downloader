## Simple file downloader via HTTP

**Building app**

```bash
mkdir build; cd build
cmake ..
make
```
Resulting programs: `downloader-cli` and `downloader-test`.


**Download a file**
```bash
./downloader-cli http://tools.ietf.org/rfc/rfc793.txt
```

If a filename can be extracted from URL, it is extracted. Otherwise, a site page is assumed to be downloaded (main page or unnamed one), and name `index.html` is used (no matter if it is really an HTML page or not). 


**Notes**
- HTTP 1.1.
- GNU/Linux (includes unistd.h, etc).
- File downloads iff URL format is supported and response is 200 OK.
- Transfer encodings are not supported.
- Error codes and unnecessary fields in response are not checked.
