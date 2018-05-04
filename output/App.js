'use strict';

var List = require("bs-platform/lib/js/list.js");
var Tree = require("./Tree.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./Utils.js");
var React = require("react");
var Shortid = require("shortid");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

var initalId = Shortid.generate();

function initialState() {
  return /* record */[/* root */Tree.addChild(Tree.makeRoot(/* () */0), /* [] */0, "")];
}

var component = ReasonReact.reducerComponent("App");

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (param) {
      var send = param[/* send */3];
      var state = param[/* state */1];
      var items = List.map((function (item) {
              return React.createElement("input", {
                          value: item[/* content */0],
                          onKeyDown: (function ($$event) {
                              var code = Utils.Dom[/* eventToKeyCode */3]($$event);
                              if (code !== 13) {
                                return /* () */0;
                              } else {
                                var path = List.rev(List.tl(List.rev(item[/* path */2])));
                                var newRoot = Tree.addChild(state[/* root */0], path, "");
                                return Curry._1(send, /* Root */[newRoot]);
                              }
                            }),
                          onChange: (function ($$event) {
                              var content = Utils.Dom[/* eventToVal */2]($$event);
                              var newRoot = Tree.walk((function (entry) {
                                      return /* record */[
                                              /* content */content,
                                              /* id */entry[/* id */1],
                                              /* path */entry[/* path */2],
                                              /* children */entry[/* children */3]
                                            ];
                                    }), state[/* root */0], item[/* path */2]);
                              return Curry._1(send, /* Root */[newRoot]);
                            })
                        });
            }), state[/* root */0][/* children */3]);
      return ReasonReact.createDomElement("div", Utils.noProps, $$Array.of_list(items));
    });
  newrecord[/* initialState */10] = initialState;
  newrecord[/* reducer */12] = (function (action, _) {
      return /* Update */Block.__(0, [/* record */[/* root */action[0]]]);
    });
  return newrecord;
}

exports.initalId = initalId;
exports.initialState = initialState;
exports.component = component;
exports.make = make;
/* initalId Not a pure module */
