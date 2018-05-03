'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Utils = require("./Utils.js");
var React = require("react");
var Shortid = require("shortid");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

var initalId = Shortid.generate();

function initialState() {
  return /* record */[/* children : array */[/* record */[
              /* content */"test",
              /* id */initalId,
              /* path : :: */[
                initalId,
                /* [] */0
              ],
              /* children : array */[]
            ]]];
}

var component = ReasonReact.reducerComponent("App");

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (param) {
      var items = $$Array.map((function (item) {
              return React.createElement("input", {
                          value: item[/* content */0],
                          onChange: (function ($$event) {
                              console.log(Utils.Dom[/* toValueOnChange */1]($$event));
                              return /* () */0;
                            })
                        });
            }), param[/* state */1][/* children */0]);
      return ReasonReact.createDomElement("div", Utils.noProps, items);
    });
  newrecord[/* initialState */10] = initialState;
  newrecord[/* reducer */12] = (function (_, _$1) {
      return /* NoUpdate */0;
    });
  return newrecord;
}

exports.initalId = initalId;
exports.initialState = initialState;
exports.component = component;
exports.make = make;
/* initalId Not a pure module */
