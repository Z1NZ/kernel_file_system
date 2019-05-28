#!/bin/sh

mkdir -p kfs_boot/boot/grub
cp kfs1 kfs_boot/boot/
echo "set timeout=1
set default=1

menuentry	\"kfs1\"	{
	multiboot /boot/kfs1
}" > kfs_boot/boot/grub/grub.cfg
