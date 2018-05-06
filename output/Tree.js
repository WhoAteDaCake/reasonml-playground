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

function isSame(e1, e2) {
  return +(e1[/* id */1] === e2[/* id */1]);
}

function hasChildren(entry) {
  return +(List.length(entry[/* children */3]) !== 0);
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

function lastChild(_item) {
  while(true) {
    var item = _item;
    if (List.length(item[/* children */3]) === 0) {
      return item;
    } else {
      _item = Utils.last(item[/* children */3]);
      continue ;
      
    }
  };
}

function walkUp(root, item) {
  var match = find(root, Utils.withoutLast(item[/* path */2]));
  if (match) {
    var parent = match[0];
    var match$1 = Utils.splitOn((function (param) {
            return isSame(item, param);
          }), parent[/* children */3]);
    var left = match$1[0];
    if (List.length(left) !== 0) {
      return lastChild(Utils.last(left));
    } else {
      return parent;
    }
  } else {
    return item;
  }
}

function walkUpWhile(predicate, root, _item, _visited) {
  while(true) {
    var visited = _visited;
    var item = _item;
    var match = find(root, Utils.withoutLast(item[/* path */2]));
    if (match) {
      var parent = match[0];
      if (Curry._3(predicate, root, parent, visited)) {
        return /* tuple */[
                parent,
                visited
              ];
      } else {
        _visited = /* :: */[
          parent,
          visited
        ];
        _item = parent;
        continue ;
        
      }
    } else {
      return /* tuple */[
              item,
              visited
            ];
    }
  };
}

function shouldStop(root, entry, visited) {
  if (isSame(entry, root)) {
    return /* true */1;
  } else {
    var partial_arg = List.hd(visited);
    var match = Utils.splitOn((function (param) {
            return isSame(partial_arg, param);
          }), entry[/* children */3]);
    return +(List.length(match[2]) !== 0);
  }
}

function walkDown(root, item) {
  if (isSame(root, item)) {
    return item;
  } else if (hasChildren(item)) {
    return List.hd(item[/* children */3]);
  } else {
    var match = find(root, Utils.withoutLast(item[/* path */2]));
    if (match) {
      var parent = match[0];
      var match$1 = Utils.splitOn((function (param) {
              return isSame(item, param);
            }), parent[/* children */3]);
      var right = match$1[2];
      if (List.length(right) !== 0) {
        return List.hd(right);
      } else {
        var match$2 = walkUpWhile(shouldStop, root, parent, /* :: */[
              parent,
              /* [] */0
            ]);
        var found = match$2[0];
        if (isSame(found, root)) {
          return item;
        } else {
          var partial_arg = List.hd(match$2[1]);
          var match$3 = Utils.splitOn((function (param) {
                  return isSame(partial_arg, param);
                }), found[/* children */3]);
          return List.hd(match$3[2]);
        }
      }
    } else {
      return item;
    }
  }
}

exports.walk = walk;
exports.find = find;
exports.isSame = isSame;
exports.hasChildren = hasChildren;
exports.makeEntry = makeEntry;
exports.makeRoot = makeRoot;
exports.appendChild = appendChild;
exports.removeChild = removeChild;
exports.addChild = addChild;
exports.withoutChild = withoutChild;
exports.lastChild = lastChild;
exports.walkUp = walkUp;
exports.walkUpWhile = walkUpWhile;
exports.shouldStop = shouldStop;
exports.walkDown = walkDown;
/* Utils Not a pure module */
