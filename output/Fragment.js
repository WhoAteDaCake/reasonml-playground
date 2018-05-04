'use strict';

var React = require("react");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

function make(children) {
  return ReasonReact.wrapJsForReason(React.Fragment, { }, children);
}

exports.make = make;
/* react Not a pure module */
