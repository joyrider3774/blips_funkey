#!/bin/sh

make clean
make TARGET=funkey

mkdir -p opk
cp blips opk/blips
cp -r ./levelpacks opk/levelpacks
cp -r ./graphics opk/graphics
cp -r ./fonts opk/fonts
cp -r ./sound opk/sound
cp -r ./music opk/music
cp Blips.funkey-s.desktop opk/Blips.funkey-s.desktop

mksquashfs ./opk Blips.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk