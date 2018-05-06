'use strict';

var Data = require("./Data.js");
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

var match = Data.load(Data.key);

var rootEntry = match ? match[0] : Tree.addChild(Tree.makeRoot(/* () */0), /* [] */0, "");

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

function handleKey(root, item, $$event, focus) {
  var code = Utils.Dom[/* eventToKeyCode */3]($$event);
  var content = Utils.Dom[/* targetValue */0]($$event.target);
  if (code >= 19) {
    var switcher = code - 38 | 0;
    if (switcher > 2 || switcher < 0) {
      return /* tuple */[
              root,
              focus
            ];
    } else {
      switch (switcher) {
        case 0 : 
            return /* tuple */[
                    root,
                    Tree.walkUp(root, item)[/* id */1]
                  ];
        case 1 : 
            return /* tuple */[
                    root,
                    focus
                  ];
        case 2 : 
            return /* tuple */[
                    root,
                    Tree.walkDown(root, item)[/* id */1]
                  ];
        
      }
    }
  } else if (code >= 8) {
    switch (code - 8 | 0) {
      case 0 : 
          if (content.length === 0) {
            var focused = Tree.walkUp(root, item);
            var partial_arg = item[/* id */1];
            var root$1 = Tree.walk((function (param) {
                    return Tree.removeChild(partial_arg, param);
                  }), root, Tree.parentPath(item));
            return /* tuple */[
                    root$1,
                    focused[/* id */1]
                  ];
          } else {
            return /* tuple */[
                    root,
                    focus
                  ];
          }
      case 5 : 
          var path = Tree.parentPath(item);
          var child = Tree.makeEntry("", path);
          return /* tuple */[
                  Tree.walk((function (param) {
                          return Tree.appendChild(child, param);
                        }), root, path),
                  child[/* id */1]
                ];
      case 1 : 
      case 2 : 
      case 3 : 
      case 4 : 
      case 6 : 
      case 7 : 
      case 8 : 
      case 9 : 
          return /* tuple */[
                  root,
                  focus
                ];
      case 10 : 
          var child$1 = Tree.makeEntry("", item[/* path */2]);
          return /* tuple */[
                  Tree.walk((function (param) {
                          return Tree.appendChild(child$1, param);
                        }), root, item[/* path */2]),
                  child$1[/* id */1]
                ];
      
    }
  } else {
    return /* tuple */[
            root,
            focus
          ];
  }
}

function make() {
  var newrecord = component.slice();
  newrecord[/* didUpdate */5] = (function (param) {
      var newSelf = param[/* newSelf */1];
      if (param[/* oldSelf */0][/* state */1][/* focus */1] !== newSelf[/* state */1][/* focus */1]) {
        Utils.Dom[/* focus */5](newSelf[/* state */1][/* focus */1]);
      }
      Data.save(Data.key, newSelf[/* state */1][/* root */0]);
      return /* () */0;
    });
  newrecord[/* render */9] = (function (param) {
      var send = param[/* send */3];
      var state = param[/* state */1];
      var renderItem = function (item) {
        return React.createElement("div", {
                    key: item[/* id */1],
                    className: "row"
                  }, React.createElement("input", {
                        id: item[/* id */1],
                        value: item[/* content */0],
                        onKeyDown: (function ($$event) {
                            var match = handleKey(state[/* root */0], item, $$event, state[/* focus */1]);
                            return Curry._1(send, /* FocusedRoot */Block.__(2, [
                                          match[0],
                                          match[1]
                                        ]));
                          }),
                        onChange: (function ($$event) {
                            return Curry._1(send, /* Root */Block.__(0, [Tree.walk((function (entry) {
                                                  return /* record */[
                                                          /* content */Utils.Dom[/* eventToVal */2]($$event),
                                                          /* id */entry[/* id */1],
                                                          /* path */entry[/* path */2],
                                                          /* children */entry[/* children */3]
                                                        ];
                                                }), state[/* root */0], item[/* path */2])]));
                          })
                      }), renderChildren(item, renderItem));
      };
      return React.createElement("div", {
                  className: "root"
                }, ReasonReact.element(/* None */0, /* None */0, Fragment.make(/* array */[$$Array.of_list(List.map(renderItem, state[/* root */0][/* children */3]))])));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* root */rootEntry,
              /* focus */List.nth(rootEntry[/* children */3], 0)[/* id */1]
            ];
    });
  newrecord[/* reducer */12] = (function (action, state) {
      switch (action.tag | 0) {
        case 0 : 
            return /* Update */Block.__(0, [/* record */[
                        /* root */action[0],
                        /* focus */state[/* focus */1]
                      ]]);
        case 1 : 
            return /* Update */Block.__(0, [/* record */[
                        /* root */state[/* root */0],
                        /* focus */action[0]
                      ]]);
        case 2 : 
            return /* Update */Block.__(0, [/* record */[
                        /* root */action[0],
                        /* focus */action[1]
                      ]]);
        
      }
    });
  return newrecord;
}

exports.component = component;
exports.rootEntry = rootEntry;
exports.renderChildren = renderChildren;
exports.handleKey = handleKey;
exports.make = make;
/* component Not a pure module */
