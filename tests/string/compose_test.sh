#!/usr/bin/bash

FORMATS=(
	'%0, %1, %3, %5'
	'%0%2%0 %1%7%7;'
	'%1=%5')
ARGS=('%**5%a' '$ARG' ',' 'łôап ныæî°' '[' '0.2548' ']' '  .')
FMT_CHECK=(
	"${ARGS[0]}, ${ARGS[1]}, ${ARGS[3]}, ${ARGS[5]}"
	"${ARGS[0]}${ARGS[2]}${ARGS[0]} ${ARGS[1]}${ARGS[7]}${ARGS[7]};"
	"${ARGS[1]}=${ARGS[5]}")

(( ${#FORMATS[@]} == ${#FMT_CHECK[@]} )) || exit 2

for ((i=0; i<${#FORMATS[@]}; i++))
do
	RESULT=$(./string_compose "${FORMATS[$i]}" "${ARGS[@]}")
	CHECK="${FMT_CHECK[$i]}"
	echo $RESULT
	echo $CHECK
	[[ $RESULT == $CHECK ]] || exit 1
done
