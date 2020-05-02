#!/bin/bash

USERNAME=pi

if [[ -n $1 ]]
then
  PROJECTNAME=$1
  HOSTS="192.168.178.73"
  PLATFORM="AtTiny85"

  #initialize directory structure
  SCRIPT="mkdir -p /home/${USERNAME}/${PLATFORM}/${PROJECTNAME}/;"
  for HOSTNAME in ${HOSTS} ; do
      ssh -l ${USERNAME} ${HOSTNAME} "${SCRIPT}"
  done

  #copy all files to pi but this script
  rsync -av -e ssh --exclude='autoInstall.sh' ./ pi@192.168.178.73:/home/pi/${PROJECTNAME}

  #flash to chip

#  SCRIPT="cd /home/${USERNAME}/${PROJECTNAME};make install;"
#  for HOSTNAME in ${HOSTS} ; do
#      ssh -l ${USERNAME} ${HOSTNAME} "${SCRIPT}"
#  done

else
  echo "No Project-Name given!"
fi
