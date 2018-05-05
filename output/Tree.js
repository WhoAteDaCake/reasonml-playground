'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./Utils.js");
var Shortid = require("shortid");

function walk(updator, entry, path) {
  if (path) {
    var rest = path[1];
    var id = path[0];
    var updatedChildren = List.map((function (child) {
            if (child[/* id */1] === id) {
              return walk(updator, child, rest);
            } else {
              return child;
            }
          }), entry[/* children */3]);
    return /* record */[
            /* content */entry[/* content */0],
            /* id */entry[/* id */1],
            /* path */entry[/* path */2],
            /* children */updatedChildren
          ];
  } else {
    return Curry._1(updator, entry);
  }
}

function find(_entry, _path) {
  while(true) {
    var path = _path;
    var entry = _entry;
    if (path) {
      var id = path[0];
      var childOpt = Utils.find((function(id){
          return function (child) {
            return +(child[/* id */1] === id);
          }
          }(id)), entry[/* children */3]);
      if (childOpt) {
        _path = path[1];
        _entry = childOpt[0];
        continue ;
        
      } else {
        return /* None */0;
      }
    } else {
      return /* Some */[entry];
    }
  };
}

function makeEntry(content, path) {
  var id = Shortid.generate();
  return /* record */[
          /* content */content,
          /* id */id,
          /* path */List.append(path, /* :: */[
                id,
                /* [] */0
              ]),
          /* children : [] */0
        ];
}

function makeRoot() {
  return /* record */[
          /* content */"",
          /* id */Shortid.generate(),
          /* path : [] */0,
          /* children : [] */0
        ];
}

function appendChild(child, parent) {
  return /* record */[
          /* content */parent[/* content */0],
          /* id */parent[/* id */1],
          /* path */parent[/* path */2],
          /* children */List.append(parent[/* children */3], /* :: */[
                child,
                /* [] */0
              ])
        ];
}

function removeChild(id, parent) {
  return /* record */[
          /* content */parent[/* content */0],
          /* id */parent[/* id */1],
          /* path */parent[/* path */2],
          /* children */List.filter((function (child) {
                    return +(child[/* id */1] !== id);
                  }))(parent[/* children */3])
        ];
}

function addChild(root, path, content) {
  var child = makeEntry(content, path);
  return walk((function (param) {
                return appendChild(child, param);
              }), root, path);
}

function withoutChild(root, child) {
  var partial_arg = child[/* id */1];
  return walk((function (param) {
                return removeChild(partial_arg, param);
              }), root, Utils.withoutLast(child[/* path */2]));
}

exports.walk = walk;
exports.find = find;
exports.makeEntry = makeEntry;
exports.makeRoot = makeRoot;
exports.appendChild = appendChild;
exports.removeChild = removeChild;
exports.addChild = addChild;
exports.withoutChild = withoutChild;
/* Utils Not a pure module */
