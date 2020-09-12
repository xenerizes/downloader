## Simple file downloader via HTTP

### Building app

```bash
mkdir build; cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
Resulting programs: `downloader-cli` and `downloader-test`.

### Download a file
```bash
./downloader-cli http://tools.ietf.org/rfc/rfc793.txt
```

If a filename can be extracted from URL, it is extracted. Otherwise, a site page is assumed to be downloaded (main page or unnamed one), and name `index.html` is used (no matter if it is really an HTML page or not). 

### Run tests

To run the tests:
```sh
sudo nginx -c $(pwd)/nginx.conf -p $(pwd)
ctest -V
```

In `Debug` CMake configuration you can also run `make cov` to see the code coverage.
Full coverage report is stored in `coverage.html` in build directory.

### Notes
- HTTP 1.1.
- GNU/Linux (includes unistd.h, etc).
- Very simple URL format.
- File downloads iff URL format is supported and response is 200 OK.
- Transfer encodings are not supported.
- Error codes and unnecessary fields in response are not checked.
- No redirections.
