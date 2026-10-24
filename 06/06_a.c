#!/bin/sh
# Create a FIFO using the shell command (GNU/Linux mknod).
rm -f /tmp/lab_fifo
mknod /tmp/lab_fifo p
ls -l /tmp/lab_fifo
