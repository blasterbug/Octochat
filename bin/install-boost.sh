#!/bin/bash

prefix=`pwd`
boost_version="1.56.0"
file_version=`echo ${boost_version} | tr . _`

if [ "$#" -ne 0 ]
then
    echo "install lib boost to the current path"
    exit 0
fi

wget http://downloads.sourceforge.net/project/boost/boost/${boost_version}/boost_${file_version}.7z
if [ "$?" -ne 0 ]
then
    echo "wget failed"
    exit 1
fi

7z x boost_${file_version}.7z
if [ "$?" -ne 0 ]
then
    echo "7z failed"
    exit 1
fi

cd ./boost_${file_version}
if [ "$?" -ne 0 ]
then
    echo "cd failed"
    exit 1
fi

./bootstrap.sh --prefix=${prefix} --with-libraries=system,thread,date_time,regex,serialization
if [ "$?" -ne 0 ]
then
    echo "bootstratp failed"
    exit 1
fi

./b2 install
if [ "$?" -ne 0 ]
then
    echo "b2 failed"
    exit 1
fi

cd ..
rm -r ./boost_${file_version}*
if [ "$?" -ne 0 ]
then
    echo "rm failed"
    exit 1
fi

exit 0
