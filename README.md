ZIP EXPLORE
==========

30.05.2013
ccs

An educational project which aims to explore and recreate the zip
archive format and compression scheme. 

## First Goal

Open an archive, list the contents, recreating `unzip -l`

## Test Data

Created random files with dd:

`dd if=/dev/random of=./test-data/foo count=10`

Create a test archive with `make-test-arc.sh`
