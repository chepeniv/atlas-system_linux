#!/usr/bin/bash

./$1 &

(kill -2 $(pidof $1);  kill -2 $(pidof $1); kill -2 $(pidof $1))

/bin/kill -9 $(pidof $1);

