MPEG 4 file

Disclaimer

My friend said I should put this disclaimer:

The program and source code contained in this repository are for general usage purposes only. We make no representations or warranties of any kind, express or implied, about the completeness, accuracy, reliability, suitability or availability with respect to program and the source code contained in this repository. Any reliance you place on such information is therefore strictly at your own risk. In no event will we be liable for any loss or damage including without limitation, indirect or consequential loss or damage, or any loss or damage whatsoever arising from loss of data or profits arising out of, or in connection with, the use / misuse / abuse of this program and source code.

[In other words, this is the Internet and you are using something that someone called The Dark Horse uploaded on a free site. Try explaining that to your boss / in-laws/ children / etc... if things don't go smoothly]

Now for the fun part.

This code is released into the public domain. Feel free to use / change as you see fit this code or parts of it.

This program is written by a hobbyist to learn / play with C++.

MPEG 4 files consist of a series of "boxes". This program reads in MPEG4 files and output this "boxes".
All boxes have some common elements / functionality. Please see BoxBase.h - this contains the class from which all other "boxes" derive.
For the most part the parser reads inside each "box" and initializes the corresponding variables. The biggest exception is the MDAT "box" - this box contains the audio and video streams. Even when available the variables are not exposed - they are only used in the Print method. We think that the users can grab this code and expose whatever variables they find useful.

Hope you find this code useful.
