#!/bin/sh

mkdir -p kfs/boot/grub
cp kfs1 
echo "set timeout=1
set default=1

menuentry	\"kfs_1\"	{
	multiboot /boot/kfs1
	boot
}" > kfs/boot/grub/grub.cfg
