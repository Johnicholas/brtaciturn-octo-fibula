'use strict';

mergeInto(LibraryManager.library, {
    new_sprite: function(which, x, y, texture_id, layer_id) {
        // console.log('new sprite', which, x, y, texture_id, layer_id);
        var it = new PIXI.Sprite(textures[texture_id])
        it.anchor.x = 0.5;
        it.anchor.y = 0.5;
        it.position.x = x;
        it.position.y = y;
        sprites[which] = it;
        // TERRIBLE HACK!
        if (layer_id == 1) {
            sprites[which].scale.x = 0.8;
            sprites[which].scale.y = 0.8;
        }
        layers[layer_id].addChild(it);
    },
    set_sprite_position: function(which, x, y, flipped) {
        if (sprites[which]) {
            sprites[which].position.x = x;
            sprites[which].position.y = y;
            if (flipped == 1) {
                sprites[which].scale.x = Math.abs(sprites[which].scale.x);
            } else {
                sprites[which].scale.x = -1 * Math.abs(sprites[which].scale.x);
            }
        }
    },
    set_sprite_tint: function(which, tint) {
        if (sprites[which]) {
            sprites[which].tint = tint;
        } else {
            console.log('cannot set sprite tint ', which);
        }
    },
    set_sprite_rotation: function(which, rotation) {
        if (sprites[which]) {
            sprites[which].rotation = rotation;
        } else {
            console.log('cannot set sprite rotation ', which);
        }
    },
    set_count: function(tier, new_value) {
        console.log('set_count', tier, new_value);
        counts[tier].text = new_value.toString();
    },
    free_sprite: function(which) {
        // console.log('free sprite', which);
        var limit = layers.length;
        var to_remove = sprites[which];
        for (i = 0; i < limit; i++) {
            layers[i].removeChild(to_remove);
        }
        delete sprites[which];
    },
    print_debug: function(message) {
        debug_message.text = Pointer_stringify(message);
    },
    set_muted: function(new_muted) {
        if (new_muted) {
            document.querySelector('audio').muted = true;
            sound_on_icon.visible = false;
        } else {
            document.querySelector('audio').muted = false;
            sound_on_icon.visible = true;
        }
    }
});

