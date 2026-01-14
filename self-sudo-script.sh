#!/bin/bash

# basically, this script acts as a login script for the purposes of applications that may
# need sudo to be able to continue without asking over and over for passwords
# needless to say, this isn't very secure, so only for vm's with burner passwords.
#
# caution: My naff humor and meme references may confuse people, but hopes the rest is useful.

# print out the prompt so the user knows this script can has too many sudo
echo -e "This script needs your password for sudo events,"
echo -n "please type your password and press enter: "

# Read the password from the script user:
read SCRIPT_SUDO_PASSWORD

#Put all the things are belongs to what you wants to scripted here!!!

#let's trigger sudo with the variable password
echo $SCRIPT_SUDO_PASSWORD |sudo -v -S

# Run all the script and program that are needs sudo!!!!

# Do the no-sudo things!!!!

# lets again trigger sudo with the variable password
echo $SCRIPT_SUDO_PASSWORD |sudo -v -S

# can has cleanup the passwrod var, don want all the pronfessional hacksmiths broke the password:
SCRIPT_SUDO_PASSWORD="qwertyuiopasdfghjklzxcvbnm1234567890mnbvcxzlkjhgfdsapoiuytrewq0987654321"

# basically, I need to figure out how to get random data to create a fake password from to
# wipe the real password out. Reason is to reduce the vulnerability window just in case.
