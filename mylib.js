'use strict';

mergeInto(LibraryManager.library, {
    printey: function() {
        Module.print('hello from lib!');
    },
    new_bunny: function(which, x, y) {
        var it = new PIXI.Sprite(PIXI.loader.resources.bunny.texture);
        it.anchor.x = 0.5;
        it.anchor.y = 0.5;
        it.position.x = x;
        it.position.y = y;
        bunnies[which] = it;
        stage.addChild(it);
    },
    free_bunny: function(which) {
        stage.removeChild(bunnies[which]);
        delete bunnies[which];
    },
    spin_bunny: function(which) {
        bunnies[which].rotation += 0.01;
    },
    set_bunny_position: function(which, x, y) {
        bunnies[which].position.x = x;
        bunnies[which].position.y = y;
    },
    new_splash: function(which) {
        stage.addChild(stages[which]);
    },
    free_splash: function(which) {
        stage.removeChild(stages[which]);
    }
});

