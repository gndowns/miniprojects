var XBoxController = require('better-xbox-controller');
var USB = require('usb');

var device = USB.findByIds(32902,41263);
var controller = new XBoxController(device);

// setting event handlers
/*
// just print the values of the sticks
function stick(side, val){
  length = val.getLength().toFixed;
  angle = val.getAngle().toFixed;
  //console.log("#{side} stick: {x:#{val.x},\ty:#{val.y}};\t" + "{l:#{length},\ta:#{angle}°}");
  console.log("length:", lenght, "angle:", angle);
}
controller.on({
  stick('left', controller.val);
});
*/
//open the controller
controller.open();
