#!/bin/sh
# Install strace if needed: sudo apt install strace
rm -f /tmp/fifo_mknod /tmp/fifo_mkfifo
echo "Tracing mknod command:"
strace -c mknod /tmp/fifo_mknod p
echo "Tracing mkfifo command:"
strace -c mkfifo /tmp/fifo_mkfifo
rm -f /tmp/fifo_mknod /tmp/fifo_mkfifo
echo "Compare syscall counts and elapsed time; results vary by machine."
