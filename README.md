# showerthoughts
![C/C++ CI](https://github.com/wporter82/showerthoughts/workflows/C/C++%20CI/badge.svg) ![Current Release](https://github.com/wporter82/showerthoughts/workflows/Current%20Release/badge.svg)

Prints out a random entry from [/r/showerthoughts](https://www.reddit.com/r/showerthoughts/hot/).

## Building

### Dependencies
The following libraries are required to compile and run `showerthoughts`:

* [libcurl](https://curl.haxx.se/)
* [json-c](https://github.com/json-c/json-c)

Before invoking `make`, install them as follows:

#### Debian
```shell
$ sudo apt install libcurl3-dev libjson-c-dev
```

#### Fedora
```shell
$ sudo dnf install libcurl-devel json-c-devel
```

### Compile

```shell
$ ./autogen.sh
$ ./configure
$ make && make install
```

## Usage

To get a showerthought displayed at the start of each interactive login shell, add this to your `.bash_profile`:

```shell
# $HOME/.bash_profile
if [[ -n $PS1 ]]; then
	if hash cowsay 2>/dev/null; then
		cowsay "$(showerthoughts)"
	else
		showerthoughts
	fi
fi
```

