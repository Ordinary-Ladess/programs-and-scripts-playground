#!/bin/bash
#Pseudo multithreading in bash script

ThreadA()
{
	while (true)
	do
		echo Thread A has variable $Var
	done
}

ThreadB()
{
	while(true)
	do
		export Var=B
		echo Thread B has variable $Var
	done
}



#todo: the script initializer and loop
#MAIN
	case $1 in
			run)
			export Var=A
			ThreadA &
			ThreadB
			;;
	*)
			self=$0
			xterm -e bash $self run &
			;;
	esac
