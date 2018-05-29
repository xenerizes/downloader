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
./downloader-cli https://tools.ietf.org/rfc/rfc793.txt
```

If a site main page is downloaded, the name `index.html` is used.
