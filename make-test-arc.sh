#!/bin/zsh
## zip up the contents of test-data
filelist=(foo bar baz)

if [ ! -d ./test-data ]; then
    echo "making test-data folder"
    mkdir ./test-data
fi

for file in $filelist; do
    if [ ! -e ./test-data/$file ]; then 
        echo "cannot find: $file"
        dd if=/dev/random of=./test-data/$file count=10
    fi
done

echo "Making test archive"
zip -v ./test-arc.zip ./test-data/*
