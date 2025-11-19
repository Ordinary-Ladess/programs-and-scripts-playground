<h1>Helpful example scripts and silly programs</h1><br>
<br>
Hopefully someone will find use in these little snippets. <br>
<br>
Apart from sound-on.sh and PseudoThreading.sh the rest are from<br>
when I was using Lenovo T400 and Dell E6400 laptops.<br>
<br>
<br>
<br>
Scripts:<br>
sound-on.sh - meant for the Zenbook Duo UX582L HDA-Codec initialization.<br>
PseudoThreading.sh - A self calling script that spawns 2 shells simultaneously.<br>
hwmon - is a self calling shell script that monitors battery state and CPU temperature,<br>
t400 - is a script to run from the run dialog of LXDE for the T400 for a few quirks of my setup.<br>
<br>
C++ programs:<br>
hwmon.cpp - is the hwmon shell script I rewrote in C++, Can't remembner if it's for the dell or lenovo<br>
hell.cpp - Abusing the compiler, mainless programming sort of... lol
hello.cpp - A functionally mainless hello world example that abuses old compiler quirks.
<br>
<br>
<br>
<h2>Purposes I had in mind</h2><br>
<br>
hwmon and the C++ rewrite I made back around 2014 (shell) to 2017 (C++),<br>
they're self explanatory, that was when similar GUI based solutions were<br>
either not packaged, or required dependencies or other situations, so I just wrote my own solution.<br>
<br>
The sound-on script I need to do further work to have it detect the machine type somehow and<br>
if the machine matches, to then run the hda parameters to switch on sound.<br>
The best way to make it run on boot on SystemD would be to hijack a service, Otherwise requires root.<br>
<br> 
PseudoThreading.sh is something I thought of recently, it's not actual multi-threading.<br>
This script I thought I might be able to use where I can have one function run say a<br>
a sudo timeout reset, a self extraction, the other function does waiting and GUI<br>
and another could do clean-up, but I've got to figure out how to communicate between since<br>
using vars don't seem to work for this. Files may leave a mess unless using /tmp I guess?<br>
<br>
hell.cpp and hello.cpp are just fun experiments that don't compile on newer compilers.<br>
<br>
<br>
<br>
<br>
All of this is done myself, with a bit of search-engine querying for a few tips, but 99.95% my own works.<br>
The only time I'll ever use Ai is for reverse engineering stuff I can't suss out, that's because<br>
it takes far less energy to do that than to leave Kw's of computer running for months on end as I<br>
attempt and fail to suss out what I'm even looking at (Yep, Reverse Engineering is a skill issue of mine)<br>
Apart from that, I refuse to use Ai for anything else.<br>

