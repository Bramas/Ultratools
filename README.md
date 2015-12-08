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

Under MIT License (MIT)

Copyright (c) 2015 Quentin Bramas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


# Author
Quentin Bramas.

Audio engine : FMOD Sound System by Firelight Technologies
