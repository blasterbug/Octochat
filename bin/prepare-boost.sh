#!/bin/bash

var_version_dot="1.57.0"
var_version_underscore="1_57_0"
var_format="tar.gz"

function func_download {
    if command -v wget
    then
        wget http://downloads.sourceforge.net/project/boost/boost/$var_version_dot/boost_$var_version_underscore.$var_format
    elif command -v curl
    then
        curl -O http://downloads.sourceforge.net/project/boost/boost/$var_version_dot/boost_$var_version_underscore.$var_format
    else
        echo "error" 1>&2
        exit 1
    fi

    if [ $? -ne 0 ]
    then
        echo "error" 1>&2
        exit 1
    fi
}

if [ $# -ne 1 ]
then
    echo "usage" 1>&2
    exit 1
fi

if [[ ! $1 =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]
then
    echo "error" 1>&2
    exit 1
fi

var_version_dot=$1
var_version_underscore=`echo $var_version_dot | tr . _`

if command -v 7z
then
    var_format="7z"
    func_download
    7z x boost_$var_version_underscore.$var_format
elif command -v tar
then
    var_format="tar.bz2"
    func_download
    tar xf boost_$var_version_underscore.$var_format
elif command -v unzip
then
    var_format="zip"
    func_download
    unzip boost_$var_version_underscore.$var_format
else
    echo "error" 1>&2
    exit 1
fi

if [ $? -ne 0 ]
then
	echo "error" 1>&2
	exit 1
fi

mv boost_$var_version_underscore boost && cd boost && ./bootstrap.sh
