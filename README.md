# Viva Pájaro

A demo is visible here: http://sugarbyte.site44.com/viva.html

## A bit of explanation

garden.ceu contains essential game logic, and the ceu compiler compiles it into _ceu_app.c.

garden.c connects to _ceu_app.c on two sides.
On the input side, it defines C functions begin(), update(), mouse_down(x, y) and so on.
On the output side, it declares that there will be functions new_sprite, set_sprite_position and so on.
You could compile garden.c with _ceu_app.c using a C compiler in order to get a "game logic library" at this point.

The command line to the emscripten compiler is in 'compile_emscripten'.
It lists the input-side functions begin, upate, mouse_down and so on that we will want to call from javascript.
On the output side, it also specifies 'mylib.js', which defines, in Javascript, functions new_sprite, set_sprite_position and so on.
It also specifies 'shell.html' as the template for the generated html.
Shell.html, via a script tag, includes 'myscript.js', which is the first element to receive control flow.
There are two fairly heavy tasks that we need to do before starting the game proper - emscripten needs to get itself set up,
and PIXI's resource loader needs to get all the assets (.pngs). So myscript.js's control flow is a BIT annoyingly callbackish. We do a few lightweight things with PIXI, and then define Module, which is what emscripten will use to get itself set up. But in the postRun field of Module, we add the function start, so after emscripten gets itself set up, we get control flow back. Start tells the PIXI resource loader to start loading pngs. Once all the pngs are loaded, then the loader will call its "once complete" callback. That sets a mousedown callback on the page, which calls the function 'reallystart'.

The point of these gyrations is to hide the emscripten and asset-loading time from the player - ideally they read the instructions, and then click, and then play the game, and don't notice the loading time (when click does nothing) - but it's a crude hack, and probably a  progress bar would be better.

'reallystart' invokes begin() directly and arranges for the input-side functions update(), mouse_down(x, y) and so on functions to be invoked at the appropriate times (using requestAnimationFrame and onmousedown).

