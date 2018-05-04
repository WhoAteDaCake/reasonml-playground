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

function appendChild(parent, child) {
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
  return walk((function (entry) {
                return appendChild(entry, child);
              }), root, path);
}

function withoutChild(root, child) {
  var partial_arg = child[/* id */1];
  return walk((function (param) {
                return removeChild(partial_arg, param);
              }), root, Utils.withoutLast(child[/* path */2]));
}

exports.walk = walk;
exports.makeEntry = makeEntry;
exports.makeRoot = makeRoot;
exports.appendChild = appendChild;
exports.removeChild = removeChild;
exports.addChild = addChild;
exports.withoutChild = withoutChild;
/* Utils Not a pure module */
