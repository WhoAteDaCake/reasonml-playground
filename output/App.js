'use strict';

var List = require("bs-platform/lib/js/list.js");
var Tree = require("./Tree.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./Utils.js");
var React = require("react");
var Fragment = require("./Fragment.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

var component = ReasonReact.reducerComponent("App");

function initialState() {
  return /* record */[/* root */Tree.addChild(Tree.makeRoot(/* () */0), /* [] */0, "")];
}

function renderChildren(item, render) {
  var match = item[/* children */3];
  if (match) {
    return React.createElement("div", {
                className: "children"
              }, ReasonReact.element(/* None */0, /* None */0, Fragment.make(/* array */[$$Array.of_list(List.map(render, item[/* children */3]))])));
  } else {
    return null;
  }
}

function handleKey(root, item, $$event) {
  var code = Utils.Dom[/* eventToKeyCode */3]($$event);
  var content = Utils.Dom[/* targetValue */0]($$event.target);
  var switcher = code - 8 | 0;
  if (switcher > 10 || switcher < 0) {
    return root;
  } else {
    switch (switcher) {
      case 0 : 
          if (content.length === 0) {
            return Tree.withoutChild(root, item);
          } else {
            return root;
          }
      case 5 : 
          var path = Utils.withoutLast(item[/* path */2]);
          return Tree.addChild(root, path, "");
      case 1 : 
      case 2 : 
      case 3 : 
      case 4 : 
      case 6 : 
      case 7 : 
      case 8 : 
      case 9 : 
          return root;
      case 10 : 
          return Tree.addChild(root, item[/* path */2], "");
      
    }
  }
}

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (param) {
      var send = param[/* send */3];
      var state = param[/* state */1];
      var renderItem = function (item) {
        return React.createElement("div", {
                    key: item[/* id */1]
                  }, React.createElement("input", {
                        className: "row",
                        id: item[/* id */1],
                        value: item[/* content */0],
                        onKeyDown: (function ($$event) {
                            return Curry._1(send, /* Root */[handleKey(state[/* root */0], item, $$event)]);
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
                      }), renderChildren(item, renderItem));
      };
      return React.createElement("div", {
                  className: "root"
                }, ReasonReact.element(/* None */0, /* None */0, Fragment.make(/* array */[$$Array.of_list(List.map(renderItem, state[/* root */0][/* children */3]))])));
    });
  newrecord[/* initialState */10] = initialState;
  newrecord[/* reducer */12] = (function (action, _) {
      return /* Update */Block.__(0, [/* record */[/* root */action[0]]]);
    });
  return newrecord;
}

exports.component = component;
exports.initialState = initialState;
exports.renderChildren = renderChildren;
exports.handleKey = handleKey;
exports.make = make;
/* component Not a pure module */
