#!/bin/sh
make
echo "$@"
echo "$@" | md5sum ; echo "$@" | ./ft_ssl
