#!/bin/sh

usage()
{
    echo "Usage:"
    echo "     $0 <file sys firmware>"
}
error()
{
    echo "error:"
    echo "    ""$1"
    exit 1
}
if [ 1 != "$#" ]; then
    usage
    exit -1
fi
flash_name="full_""${1##*/}"
if [ ! -f "$1" ];then
    error "$1"" not exist!"
fi
ub="u-boot.bin"
ube="u-boot-env.bin"
fac="factory.bin"
if [ ! -f "$ub" ] ;then
    error "$ub not exist in current dir!"
fi
if [ ! -f "$ube" ] ;then
    error "$ube not exist in current dir!"
fi
if [ ! -f "$fac" ] ;then
    error "$fac not exist in current dir!"
fi
test -d bin || mkdir bin
./mkflash/makeflash bin/$flash_name u-boot.bin 30000 u-boot-env.bin 10000 factory.bin 10000 $1 7B0000
