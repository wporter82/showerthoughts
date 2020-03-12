#!/bin/sh

(autoreconf --version) < /dev/null > /dev/null || {
	echo "You must have autoreconf installed."
	DIE=1
}
(automake --version) < /dev/null > /dev/null || {
	echo "You must have automake installed to generate procps-ng build system."
	DIE=1
}

echo "Generating build-system by:"
echo "    autoreconf: $(autoreconf --version | head -1)"
echo "    aclocal: $(aclocal --version | head -1)"
echo "    automake: $(automake --version | head -1)"

autoreconf --install

echo
echo "Now type './configure' and 'make && make install' to compile and install."
