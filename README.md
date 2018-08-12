SDL2 for liborbis
======================
 
 What does this do?
===================
 
  This is an unofficial port of SDL2.0 for PlayStation 4 using liborbis. It is ugly and some functionalities are not tested. I have no idea about SDL and the base port have been done in less than 24 hours porting from VITA code so sure you could improve it and make it much better than me or port it for other libraries. No intention from me to maintain it.
  
  You can get a little sample in liborbis repository with video and pad using SDL. Audio is using directly liborbis although i have implemented audio part on SDL i have not tested it, but i left some init method for externals libraries on liborbisAudio to avoid callbacl function and control buffer population with your own hands [link](https://github.com/orbisdev/liborbis/commit/167f8d61984b8ace2991418f41159b1a61fea617#diff-1d1e79ba191df6d3daea56c6f444709a), feel free to test it.
  
  Sample [link](https://github.com/orbiesdev/liborbis/samples/sdl)
  

 Credits
===========================
  
  Special thanks goes to:
  
  - xerpi,Cpajuste,rsn8887 and others who made SDL-Vita port without it i could not been done it.
  - Hitodama for his incredible work with ps4sdk.
  - All people involved with liborbis.
  - Of course to the SDL crew for all this stuff.