# showerthoughts

Prints out a random entry from the "hot" category of the [subreddit of the same name](https://www.reddit.com/r/showerthoughts/hot/).

## Building

The following libraries are required to compile and run `showerthoughts`:

* [libcurl](https://curl.haxx.se/)
* [json-c](https://github.com/json-c/json-c)

Before invoking `make`, install them as follows:

* Debian
  ```shell
  sudo apt install libcurl3-dev libjson-c-dev
  ```

* Fedora
  ```shell
  sudo dnf install libcurl-devel json-c-devel
  ```

## Installing

To get a showerthought displayed at each start of an interactive login shell, execute these statements:

```shell
install showerthoughts $HOME/.local/bin

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

And make sure `$HOME/.local/bin` is in `$PATH`.

