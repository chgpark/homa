#!/bin/sh
ldapsearch -Q "uid=z*" | grep "cn:" | cut -b"5-" | sort -r

