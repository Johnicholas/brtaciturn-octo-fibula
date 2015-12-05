'use strict';

mergeInto(LibraryManager.library, {
    printey: function() {
        Module.print('hello from lib!');
    },
    new_bunny: function(key, x, y) {
        var it = new PIXI.Sprite(PIXI.loader.resources.bunny.texture);
        it.anchor.x = 0.5;
        it.anchor.y = 0.5;
        it.position.x = x;
        it.position.y = y;
        bunnies[key] = it;
        stage.addChild(it);
    },
    spin_bunny: function(key) {
        bunnies[key].rotation += 0.01;
    },
});

