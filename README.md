# Cheaptune - simple yet powerfull chiptune generator
## by SkyWodd

"Cheaptune" is a total rework from scratch of my previous chiptune generator attempt.

This version use object oriented programmation strategy, no more "pseudo-object" oriented C code.
No more crap, no more "spaghetti include", only clean C++ code.

**BREAKING NEWS**
Version 2.0 is out !

Changelog:

+ Extensible (virtual class based code. You can now add custom waveform generator, envelope, ...)
+ Fast execution (old switch based code VS virtual function call: same performance with GCC)
+ Integer 16/32 bits calculation ONLY (no more fuck*ng float !)
+ Exponential response using precomputed tables (ultra fast)
+ Sinus wave table optimized (1/4 sinus wave required instead of full table in v1.0)
+ Special low frequency oscillator available
+ Improved audio resolution, now full 16 bits
+ Adjustable frequency synthesis resolution, from 9 bits to full 16 bits
+ Automated wave table generation (python script)


TODO list:

+ Filter rework, goal: 100% integer based code (removed for now)
+ Vibrato oscillator
+ Tremolo envelope
+ Ring modulation
+ Hard sync
+ Tracker-like music sheet decoder 

---
### Source code

The code itself is commented to provide implementation details.
The whole source code is released under the GPLv3 license.

To compile the source code you only need to get an GCC-based compiler with C++ support.
Remarks : I'm using Eclipse IDE with built-in builder, so no makefile for now. 

---
### References

Here a list of URL used to create this program :

+ SID sound chip details : http://www.waitingforfriday.com/index.php/Commodore_SID_6581_Datasheet
+ Direct digital synthesis whitepaper : http://www.analog.com/library/analogDialogue/archives/38-08/dds.html
+ ADSR envelope : http://www.music.mcgill.ca/~gary/306/week12/envelopes.html
+ Audio mixing theory : http://www.vttoth.com/CMS/index.php/technical-notes/68
+ Audio mixing implementation : http://atastypixel.com/blog/how-to-mix-audio-samples-properly-on-ios/
+ IIR High-pass filter formula : http://en.wikipedia.org/wiki/High-pass_filter
+ IIR Low-pass filter formula : http://en.wikipedia.org/wiki/Low-pass_filter
+ Oscillator sync theory : http://en.wikipedia.org/wiki/Oscillator_sync#Hard_Sync
+ Ring modulation theory : http://fr.wikipedia.org/wiki/Ring_Modulator
