#!/bin/bash
make
make re
echo $(diff <(./cust) <(./comp))
