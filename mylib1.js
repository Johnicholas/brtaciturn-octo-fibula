'use strict';

mergeInto(LibraryManager.library, {
    printey: function() {
        Module.print('hello from lib!');
    },
    spin_bunny: function() {
        bunny.rotation += 0.01;
    },
});

