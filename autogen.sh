#!/bin/sh

(autoreconf --version) < /dev/null > /dev/null || {
	echo "You must have autoreconf installed."
	DIE=1
}

echo "Generating build-system by:"
echo "    autoreconf: $(autoreconf --version | head -1)"

autoreconf --install

echo
echo "Now type './configure' and 'make && make install' to compile and install."
