#!/bin/bash

# 检查一些系统环境变量.
# 这是一种可以做一些预防性保护措施的好习惯.
# 比如, 如果$USER(用户在控制台上中的名字)没有被设置的话,
#+ 那么系统就会不认你.
: ${HOSTNAME?} ${USER?} ${HOME?} #${MAIL?}
  echo
  echo "Name of the machine is $HOSTNAME."
  echo "You are $USER."
  echo "Your home directory is $HOME."
  echo "Your mail INBOX is located in $MAIL."
  echo
  echo "If you are reading this message,"
  echo "critical environmental variables have been set."
  echo
  echo
 
