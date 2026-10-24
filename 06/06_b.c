#!/bin/sh
rm -f /tmp/lab_fifo
mkfifo /tmp/lab_fifo
ls -l /tmp/lab_fifo
