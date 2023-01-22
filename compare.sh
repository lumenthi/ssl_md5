#!/bin/bash
# echo "$@"
# echo "$@" | md5sum ; echo "$@" | ./ft_ssl md5 -r
# echo "$@" | sha256sum ; echo "$@" | ./ft_ssl sha256 -r

touch /tmp/file
i=0

until [ $i -gt 10000 ]
do
  # echo -n $i >> /tmp/file
  echo -n a >> /tmp/file
  diff <(md5sum /tmp/file) <(./ft_ssl md5 -r /tmp/file)
  diff <(sha256sum /tmp/file) <(./ft_ssl sha256 -r /tmp/file)
  ((i=i+1))
done

rm /tmp/file
