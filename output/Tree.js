'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ListRe = require("./utils/ListRe.js");
var Shortid = require("shortid");

function eq(e1, e2) {
  return +(e1[/* id */1] === e2[/* id */1]);
}

function hasChildren(entry) {
  return +(List.length(entry[/* children */3]) !== 0);
}

function parentPath(entry) {
  return ListRe.butLast(entry[/* path */2]);
}

function createEntry(content, path) {
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

function createRoot(content) {
  return /* record */[
          /* content */content,
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

function updateContent(content, entry) {
  return /* record */[
          /* content */content,
          /* id */entry[/* id */1],
          /* path */entry[/* path */2],
          /* children */entry[/* children */3]
        ];
}

function deepUpdate(fn, entry, path) {
  if (path) {
    var rest = path[1];
    var id = path[0];
    return /* record */[
            /* content */entry[/* content */0],
            /* id */entry[/* id */1],
            /* path */entry[/* path */2],
            /* children */List.map((function (child) {
                    if (child[/* id */1] === id) {
                      return deepUpdate(fn, child, rest);
                    } else {
                      return child;
                    }
                  }), entry[/* children */3])
          ];
  } else {
    return Curry._1(fn, entry);
  }
}

function updateParent(fn, root, entry) {
  return deepUpdate(fn, root, ListRe.butLast(entry[/* path */2]));
}

exports.eq = eq;
exports.hasChildren = hasChildren;
exports.parentPath = parentPath;
exports.createEntry = createEntry;
exports.createRoot = createRoot;
exports.appendChild = appendChild;
exports.removeChild = removeChild;
exports.updateContent = updateContent;
exports.deepUpdate = deepUpdate;
exports.updateParent = updateParent;
/* shortid Not a pure module */
