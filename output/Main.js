'use strict';

var ReactVega = require("react-vega");

function listenerName(str) {
  return ReactVega.default.listenerName(str);
}

console.log(ReactVega.default.listenerName("mad"));

exports.listenerName = listenerName;
/*  Not a pure module */
