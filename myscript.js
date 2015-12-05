'use strict'

document.onkeydown = function document_onkeydown(event) {
  switch (event.keyCode) {
    case 38: // Up
      event.preventDefault();
      Module.ccall('up_key_down', null, [], []);
      break
    case 37: // Left
      event.preventDefault();
      Module.ccall('left_key_down', null, [], []);
      break
    case 39: // Right
      event.preventDefault();
      Module.ccall('right_key_down', null, [], []);
      break
  }
}

document.onkeyup = function document_onkeyup(event) {
  switch (event.keyCode) {
    case 38: // Up
      event.preventDefault();
      Module.ccall('up_key_up', null, [], []);
      break
    case 37: // Left
      event.preventDefault();
      Module.ccall('left_key_up', null, [], []);
      break
    case 39: // Right
      event.preventDefault();
      Module.ccall('right_key_up', null, [], []);
      break
  }
}

var renderer = PIXI.autoDetectRenderer(600, 400);
document.body.appendChild(renderer.view);
var stage = new PIXI.Container();

PIXI.loader.add('background', 'background.png');
PIXI.loader.add('background2', 'background2.png');
PIXI.loader.add('background3', 'background3.png');
PIXI.loader.add('enemybuggy', 'enemybuggy.png');
PIXI.loader.add('enemybullet', 'enemybullet.png');
PIXI.loader.add('enemycircle', 'enemycircle.png');
PIXI.loader.add('enemydummy', 'enemydummy.png');
PIXI.loader.add('enemyshooter', 'enemyshooter.png');
PIXI.loader.add('enemyspawner', 'enemyspawner.png');
PIXI.loader.add('enemyturret', 'enemyturret.png');
PIXI.loader.add('explosion', 'explosion.png');
PIXI.loader.add('hudscore', 'hudscore.png');
PIXI.loader.add('hudshield', 'hudshield.png');
PIXI.loader.add('hudspeed', 'hudspeed.png');
PIXI.loader.add('lasers', 'lasers.png');
PIXI.loader.add('money', 'money.png');
PIXI.loader.add('option', 'option.png');
PIXI.loader.add('regularbullet', 'regularbullet.png');
PIXI.loader.add('regularbullettrail', 'regularbullettrail.png');
PIXI.loader.add('shield', 'shield.png');
PIXI.loader.add('splash0', 'splash0.png');
PIXI.loader.add('splash1', 'splash1.png');
PIXI.loader.add('starfield', 'starfield.png');
PIXI.loader.add('thrust', 'thrust.png');
PIXI.loader.add('tileset1', 'tileset1.png');
PIXI.loader.add('tileset2', 'tileset2.png');
PIXI.loader.add('tilesetbreakable', 'tilesetbreakable.png');
PIXI.loader.add('title', 'title.png');
PIXI.loader.add('vipergirl', 'vipergirl.png');
PIXI.loader.add('vipertitlescreenughpleasework', 'vipertitlescreenughpleasework.png');
PIXI.loader.add('bunny', 'bunny.png');

var bunnies = [];

function tick() {
    Module.ccall('update', null, [], []);
    renderer.render(stage);
    requestAnimationFrame(tick);
}

PIXI.loader.once('complete', function () {
    Module.ccall('begin', null, [], []);
    tick();
});

var Module = {
    preRun: [],
    postRun: [],
    print: function (text) {
        console.log(text)
    },
    printErr: function (text) {
        console.error(text)
    },
    setStatus: function(text) {
        console.log('status: ' + text);
    },
    totalDependencies: 0,
    monitorRunDependencies: function(left) {
        console.log('monitorRunDependencies: ' + left);
    }
};
