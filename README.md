# showerthoughts
![C/C++ CI](https://github.com/wporter82/showerthoughts/workflows/C/C++%20CI/badge.svg)![Create Release](https://github.com/wporter82/showerthoughts/workflows/Create%20Release/badge.svg)

Prints out a random entry from the "hot" category of the [subreddit of the same name](https://www.reddit.com/r/showerthoughts/hot/).

## Building

The following libraries are required to compile and run `showerthoughts`:

* [libcurl](https://curl.haxx.se/)
* [json-c](https://github.com/json-c/json-c)

Before invoking `make`, install them as follows:

* Debian
  ```shell
  $ sudo apt install libcurl3-dev libjson-c-dev
  ```

* Fedora
  ```shell
  $ sudo dnf install libcurl-devel json-c-devel
  ```

```shell
$ ./autogen.sh
$ ./configure
$ make && make install
```

## Usage

To get a showerthought displayed at each start of an interactive login shell, execute these statements:

```shell
cat <<'END' >>$HOME/.bash_profile
if [[ -n $PS1 ]]; then
	if hash cowsay 2>/dev/null; then
		cowsay "$(showerthoughts)"
	else
		showerthoughts
	fi
fi
END
```

