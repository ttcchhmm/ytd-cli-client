# ytd-cli-client : a minimal client for ytd
This is a minimal implementation of a client for [ytd](https://github.com/ttcchhmm/ytd).

## Usage
```
ytd-cli-client [options] serverAddress port request argument

Options:
  -h, --help     Displays help on commandline options.
  --help-all     Displays help including Qt specific options.
  -v, --version  Displays version information.

Arguments:
  serverAddress The address to the ytd server
  port           The port used by the ytd server
  request        The type of request to send to the server
  argument       The argument for the request if needed
```

To see what requests and arguments are supported, please see the [protocol documentation](https://github.com/ttcchhmm/ytd/blob/master/docs/Protocol.md).

## Dependencies
- Qt Core
- Qt WebSockets
- `qmake` (build)

## How to build
First create a build directory :
```bash
mkdir build
cd build
```

Then generate the `Makefile` :
```bash
qmake -makefile ../ytd.pro
```

And finally compile :
```bash
make -j$(nproc)
```