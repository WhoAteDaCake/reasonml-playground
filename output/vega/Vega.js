'use strict';

var ReactVega = require("react-vega");

((window.vega = ReactVega));

function listenerName(str) {
  return ReactVega.default.listenerName(str);
}

exports.listenerName = listenerName;
/*  Not a pure module */
