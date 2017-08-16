#!/bin/sh

usage()
{
    echo "Usage:"
    echo "     $0 <firmware> <8|16>"
}
error()
{
    echo "error:"
    echo "    ""$1"
    exit 1
}
if [ 2 != "$#" ]; then
    usage
    exit -1
fi
#flash_name="full_""${1##*/}"
if [ ! -f "$1" ];then
    error "$1"" not exist!"
fi
#ub="u-boot.bin"
#ube="u-boot-env.bin"
#if [ ! -f "$ub" ] ;then
#    error "$ub not exist in current dir!"
#fi
#if [ ! -f "$ube" ] ;then
#    error "$ube not exist in current dir!"
#fi

case $2 in
	16)
	    flash_name="full_""${1##*/}"
            fac="factory-16.bin"
            if [ ! -f "$fac" ] ;then
                error "$fac not exist in current dir!"
            fi
            test -d bin || mkdir bin
	    echo $flash_name
            ./mkflash/makeflash bin/$flash_name u-boot-16.bin 30000 u-boot-env.bin 10000 $fac 10000 $1 FB0000

	;;
	8)
	    flash_name="full_""${1##*/}"
            fac="factory-8.bin"
            if [ ! -f "$fac" ] ;then
                error "$fac not exist in current dir!"
            fi
            test -d bin || mkdir bin
            ./mkflash/makeflash bin/$flash_name u-boot-8.bin 30000 u-boot-env.bin 10000 $fac 10000 $1 7B0000

	;;	
	*)
	   usage
	   exit -1 
	;;
esac
