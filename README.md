# Ultratools

This is the git repository of Ultratools Editor, an editor for ultrastar songs.
Ultratools is available for windows, mac os and linux.
The binaries for mac and windows are available on sourceforge.

I accept with pleasure any idea and remark to improve the editor. Please make a pull request.

# Building Ultratools

[![Build Status](https://travis-ci.org/Bramas/Ultratools.svg?branch=master)](https://travis-ci.org/Bramas/Ultratools)

## On Linux

Require Qt >= 5.2.0

On Ubuntu >= 14.04

install qt:

    sudo apt-get install qtbase5-dev qttools5-dev-tools

install fmodex:
download the last version of fmodex, then:

    tar xvf fmodapi<VERSION_NUMBER>linux.tar.gz
    sudo cp -r fmodapi<VERSION_NUMBER>linux/api/lib/* /usr/local/lib/.
    sudo mkdir /usr/local/include/fmod/
    sudo cp -r fmodapi<VERSION_NUMBER>linux/api/inc/* /usr/local/include/fmod/.


## On Mac Os X

Require Qt >= 5.4.0

## On Windows

Require Qt >= 5.4.0


# Licence

"THE BEER-WARE LICENSE" (Revision 42):
Quentin Bramas <quentin@bramas.fr> wrote those files. As long as you retain this notice you
can do whatever you want with this stuff. If we meet some day, and you think
this stuff is worth it, you can buy me a beer in return Quentin Bramas

"LICENCE BEERWARE" (Révision 42):
Quentin Bramas <quentin@bramas.fr> a créé ces fichiers. Tant que vous conservez cet avertissement,
vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
retour. Quentin Bramas

# Author
Quentin Bramas.

Audio engine : FMOD Sound System by Firelight Technologies
