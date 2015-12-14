'use strict'

var renderer = new PIXI.WebGLRenderer(1280, 900);

var stage = new PIXI.Container();
var bg = new PIXI.Container();
stage.addChild(bg);
var mg1 = new PIXI.Container();
stage.addChild(mg1);
var mg2 = new PIXI.Container();
stage.addChild(mg2);
var fg = new PIXI.Container();
stage.addChild(fg);
var lighting = new PIXI.Container();
stage.addChild(lighting);

var layers = [bg, mg1, mg2, fg, lighting];

PIXI.loader.add('background', 'bg.png');
PIXI.loader.add('lighting', 'lighting.png');
// PIXI.loader.add('dirt', 'dirt.png');
PIXI.loader.add('growing', 'sprout.png');
//PIXI.loader.add('flourishing', 'philo_REPLACE.png');
//PIXI.loader.add('overgrown', 'overgrown.png');
PIXI.loader.add('watering_can', 'watering-icon.png');
// PIXI.loader.add('watering_can_tilted', 'watering_can_tilted.png');
// PIXI.loader.add('birb1', 'birb1_REPLACE.png');
// PIXI.loader.add('birb2', 'birb2_REPLACE.png');
PIXI.loader.add('shovel', 'dig-icon.png');
PIXI.loader.add('bag_of_seeds', 'seed-icon.png');
PIXI.loader.add('philodendron', 'philo.png');
PIXI.loader.add('orchid', 'orchi.png');
PIXI.loader.add('pitcher', 'pitcher.png');
PIXI.loader.add('heliconia', 'heliconia.png');
PIXI.loader.add('birb1_flying', 'birbs_f.png');
PIXI.loader.add('birb1_sitting', 'birbs_s.png');
PIXI.loader.add('birb2_flying', 'birbs3_f.png');
PIXI.loader.add('birb2_sitting', 'birbs3_s.png');
PIXI.loader.add('birb3_flying', 'birbs2_f.png');
PIXI.loader.add('birb3_sitting', 'birbs2_s.png');
PIXI.loader.add('seed', 'knob.png');
PIXI.loader.add('sound_on', 'sound_ON-icon.png');
PIXI.loader.add('sound_off', 'sound_OFF-icon.png');

var sprites = [];
var textures = [];
var sound_on_icon;

var debug_message = new PIXI.Text("", {font: "50px Arial", fill: "white"});
var counts = [
  new PIXI.Text("\u221E", {font: "20px Arial", fill: "black"}),
  new PIXI.Text("0", {font: "20px Arial", fill: "black"}),
  new PIXI.Text("0", {font: "20px Arial", fill: "black"}),
  new PIXI.Text("0", {font: "20px Arial", fill: "black"}),
];

function tick() {
    Module.ccall('update', null, [], []);
    renderer.render(stage);
    requestAnimationFrame(tick);
}

function reallystart() {
    // textures[1] = PIXI.loader.resources.dirt.texture;
    textures[2] = PIXI.loader.resources.growing.texture;
    // textures[3] = PIXI.loader.resources.flourishing.texture;
    // textures[4] = PIXI.loader.resources.overgrown.texture;
    textures[5] = PIXI.loader.resources.watering_can.texture;
    // textures[6] = PIXI.loader.resources.watering_can_tilted.texture;
    // textures[7] = PIXI.loader.resources.birb2.texture;
    // textures[8] = PIXI.loader.resources.birb1.texture;
    textures[9] = PIXI.loader.resources.philodendron.texture;
    textures[10] = PIXI.loader.resources.orchid.texture;
    textures[11] = PIXI.loader.resources.heliconia.texture;
    textures[12] = PIXI.loader.resources.pitcher.texture;
    textures[13] = PIXI.loader.resources.shovel.texture;
    textures[14] = PIXI.loader.resources.bag_of_seeds.texture;
    textures[15] = PIXI.loader.resources.birb1_flying.texture;
    textures[16] = PIXI.loader.resources.birb1_sitting.texture;
    textures[17] = PIXI.loader.resources.birb2_flying.texture;
    textures[18] = PIXI.loader.resources.birb2_sitting.texture;
    textures[19] = PIXI.loader.resources.birb3_flying.texture;
    textures[20] = PIXI.loader.resources.birb3_sitting.texture;
    textures[21] = PIXI.loader.resources.seed.texture;

    bg.addChild(new PIXI.Sprite(PIXI.loader.resources.background.texture));
    var x_cursor = 215;
    var shovel_icon = new PIXI.Sprite(PIXI.loader.resources.shovel.texture);
    shovel_icon.position.x = x_cursor;
    x_cursor += 135;
    shovel_icon.position.y = 850;
    shovel_icon.anchor.x = 0.5;
    shovel_icon.anchor.y = 0.5;
    bg.addChild(shovel_icon);
    var watering_can_icon = new PIXI.Sprite(PIXI.loader.resources.watering_can.texture);
    watering_can_icon.position.x = x_cursor;
    x_cursor += 135;
    watering_can_icon.position.y = 850;
    watering_can_icon.anchor.x = 0.5;
    watering_can_icon.anchor.y = 0.5;
    bg.addChild(watering_can_icon);
    for (var i = 0; i < 4; i++) {
        var bag_icon = new PIXI.Sprite(PIXI.loader.resources.bag_of_seeds.texture);
        bag_icon.position.x = x_cursor;
        bag_icon.position.y = 850;
        bag_icon.anchor.x = 0.5;
        bag_icon.anchor.y = 0.5;
        bg.addChild(bag_icon);
        counts[i].position.x = x_cursor + 30;
        counts[i].position.y = 850 + 10;
        bg.addChild(counts[i]);
        x_cursor += 135;
    }
    var sound_off_icon = new PIXI.Sprite(PIXI.loader.resources.sound_off.texture);
    sound_off_icon.position.x = x_cursor;
    x_cursor += 135;
    sound_off_icon.position.y = 850;
    sound_off_icon.anchor.x = 0.5;
    sound_off_icon.anchor.y = 0.5;
    bg.addChild(sound_off_icon);

    sound_on_icon = new PIXI.Sprite(PIXI.loader.resources.sound_on.texture);
    sound_on_icon.position.x = sound_off_icon.position.x;
    sound_on_icon.position.y = sound_off_icon.position.y;
    sound_on_icon.anchor.x = 0.5;
    sound_on_icon.anchor.y = 0.5;
    bg.addChild(sound_on_icon);

    lighting.addChild(new PIXI.Sprite(PIXI.loader.resources.lighting.texture));
    lighting.addChild(debug_message);
    tick();

    renderer.view.onmousedown = function canvas_onmousedown(event) {
        var x = event.pageX - renderer.view.offsetLeft;
        var y = event.pageY - renderer.view.offsetTop;
        Module.ccall('mouse_down', null, ['number', 'number'], [x, y]);
    }
    
    renderer.view.onmouseup = function canvas_onmouseup(event) {
        var x = event.pageX - renderer.view.offsetLeft;
        var y = event.pageY - renderer.view.offsetTop;
        Module.ccall('mouse_up', null, ['number', 'number'], [x, y]);
    }
    
    renderer.view.onmouseover = function canvas_onmouseover(event) {
        var x = event.pageX - renderer.view.offsetLeft;
        var y = event.pageY - renderer.view.offsetTop;
        Module.ccall('mouse_over', null, ['number', 'number'], [x, y]);
    }
    
    renderer.view.onmousemove = function canvas_onmousemove(event) {
        var x = event.pageX - renderer.view.offsetLeft;
        var y = event.pageY - renderer.view.offsetTop;
        Module.ccall('mouse_move', null, ['number', 'number'], [x, y]);
    }
    
    renderer.view.onmouseout = function canvas_onmousemove(event) {
        Module.ccall('mouse_out', null, [], []);
    }
    
    renderer.view.oncontextmenu = function canvas_oncontextmenu(event) {
        return false;
    }
    Module.ccall('begin', null, [], []);
    document.querySelector('img').style.display = 'none';
    document.body.appendChild(renderer.view);
}

PIXI.loader.once('complete', function () {
    console.log('pixi loader complete');

    document.querySelector('img').onmousedown = function canvas_onmousedown(event) {
        reallystart();
    }
});

function start() {
    PIXI.loader.load();
}

var Module = {
    preRun: [],
    postRun: [start],
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
