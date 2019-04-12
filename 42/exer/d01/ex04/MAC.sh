#!/bin/sh
ifconfig -a | grep ether | cut -c8-24
