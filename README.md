# Cheaptune - simple yet powerfull chiptune generator
## by SkyWodd

"Cheaptune" is a total rework from scratch of my previous chiptune generator attempt.

This version use object oriented programmation strategy, no more "pseudo-object" oriented C code.
No more crap, no more "spaghetti include", only clean C++ code.

---
### Source code

The code itself is commented to provide implementation details.
The whole source code is released under the GPLv3 license.
To compile this source code you only need to get an GCC-based compiler with basic C++ support.

Here a list of references used to create this program :
+ SID sound chip details : http://www.waitingforfriday.com/index.php/Commodore_SID_6581_Datasheet
+ Direct digital synthesis whitepaper : http://www.analog.com/library/analogDialogue/archives/38-08/dds.html
+ ADSR envelope : http://www.music.mcgill.ca/~gary/306/week12/envelopes.html
+ Audio mixing theory : http://www.vttoth.com/CMS/index.php/technical-notes/68
+ Audio mixing implementation : http://atastypixel.com/blog/how-to-mix-audio-samples-properly-on-ios/
+ IIR High-pass filter formula : http://en.wikipedia.org/wiki/High-pass_filter
+ IIR Low-pass filter formula : http://en.wikipedia.org/wiki/Low-pass_filter
+ Oscillator sync theory : http://en.wikipedia.org/wiki/Oscillator_sync#Hard_Sync
+ Ring modulation theory : http://fr.wikipedia.org/wiki/Ring_Modulator

---
### Technical details

+ 8 bits sound output quality
+ 7 waveform per oscillator/channel (None, DC, Sinus, Triangle, Square, Sawtooth, Noise)
+ Oscillator sync and ring modulation support (work in progress)
+ ADSR envelope per channel with linear or exponential response (full user defined)
+ Compilation-time definable number of channels
+ Global mixer with volume control and independent volume control per channel
+ 5 digital filter available (passthrough, low-pass, high-pass, band-pass, notch) (Work in progress)
+ Integrated tracker-bytecode decoder (TODO)

Warning: Require floating point math for exponential response and filter (if used).