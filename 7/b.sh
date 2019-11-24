#!/bin/bash
a=$(./a.out < input)
sed "s/^\(.*\) -> b$/$a -> b/" input | ./a.out
