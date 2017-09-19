var GamePad = require( 'node-gamepad' );
var controller = new GamePad('logitech/dualaction');
controller.connect();
console.log("here");
controller.on( '9:press', function() {
    console.log( 'up' );
} );
controller.on( 'down:press', function() {
    console.log( 'down' );
} );
