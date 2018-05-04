'use strict';

var List = require("bs-platform/lib/js/list.js");
var Tree = require("./Tree.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./Utils.js");
var React = require("react");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

var component = ReasonReact.reducerComponent("App");

function initialState() {
  return /* record */[/* root */Tree.addChild(Tree.makeRoot(/* () */0), /* [] */0, "")];
}

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (param) {
      var send = param[/* send */3];
      var state = param[/* state */1];
      var renderItem = function (item) {
        var match = item[/* children */3];
        var items = match ? ReasonReact.createDomElement("div", {
                className: "children"
              }, $$Array.of_list(List.map(renderItem, item[/* children */3]))) : React.createElement("div", {
                className: "hidden"
              });
        return React.createElement("div", undefined, React.createElement("input", {
                        className: "row",
                        id: item[/* id */1],
                        value: item[/* content */0],
                        onKeyDown: (function ($$event) {
                            var code = Utils.Dom[/* eventToKeyCode */3]($$event);
                            var content = Utils.Dom[/* targetValue */0]($$event.target);
                            var switcher = code - 8 | 0;
                            var newRoot;
                            if (switcher > 10 || switcher < 0) {
                              newRoot = state[/* root */0];
                            } else {
                              switch (switcher) {
                                case 0 : 
                                    newRoot = content.length === 0 ? Tree.withoutChild(state[/* root */0], item) : state[/* root */0];
                                    break;
                                case 5 : 
                                    var path = Utils.withoutLast(item[/* path */2]);
                                    newRoot = Tree.addChild(state[/* root */0], path, "");
                                    break;
                                case 1 : 
                                case 2 : 
                                case 3 : 
                                case 4 : 
                                case 6 : 
                                case 7 : 
                                case 8 : 
                                case 9 : 
                                    newRoot = state[/* root */0];
                                    break;
                                case 10 : 
                                    newRoot = Tree.addChild(state[/* root */0], item[/* path */2], "");
                                    break;
                                
                              }
                            }
                            return Curry._1(send, /* Root */[newRoot]);
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
                      }), items);
      };
      var items = List.map(renderItem, state[/* root */0][/* children */3]);
      return ReasonReact.createDomElement("div", {
                  className: "root"
                }, $$Array.of_list(items));
    });
  newrecord[/* initialState */10] = initialState;
  newrecord[/* reducer */12] = (function (action, _) {
      return /* Update */Block.__(0, [/* record */[/* root */action[0]]]);
    });
  return newrecord;
}

exports.component = component;
exports.initialState = initialState;
exports.make = make;
/* component Not a pure module */
