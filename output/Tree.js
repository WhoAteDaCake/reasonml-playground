'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./utils/Utils.js");
var ListRe = require("./utils/ListRe.js");
var Shortid = require("shortid");

function eq(e1, e2) {
  return e1[/* id */1] === e2[/* id */1];
}

function hasChildren(entry) {
  return List.length(entry[/* children */3]) !== 0;
}

function parentPath(entry) {
  return ListRe.butLast(entry[/* path */2]);
}

function createEntry(content, path) {
  var id = Shortid.generate();
  return /* record */Block.record([
            "content",
            "id",
            "path",
            "children"
          ], [
            content,
            id,
            List.append(path, /* :: */Block.variant("::", [
                    id,
                    /* [] */0
                  ])),
            0
          ]);
}

function createRoot(content) {
  return /* record */Block.record([
            "content",
            "id",
            "path",
            "children"
          ], [
            content,
            Shortid.generate(),
            0,
            0
          ]);
}

function appendChild(child, parent) {
  return /* record */Block.record([
            "content",
            "id",
            "path",
            "children"
          ], [
            parent[/* content */0],
            parent[/* id */1],
            parent[/* path */2],
            List.append(parent[/* children */3], /* :: */Block.variant("::", [
                    child,
                    /* [] */0
                  ]))
          ]);
}

function removeChild(id, parent) {
  return /* record */Block.record([
            "content",
            "id",
            "path",
            "children"
          ], [
            parent[/* content */0],
            parent[/* id */1],
            parent[/* path */2],
            List.filter((function (child) {
                      return child[/* id */1] !== id;
                    }))(parent[/* children */3])
          ]);
}

function updateContent(content, entry) {
  return /* record */Block.record([
            "content",
            "id",
            "path",
            "children"
          ], [
            content,
            entry[/* id */1],
            entry[/* path */2],
            entry[/* children */3]
          ]);
}

function deepUpdate(fn, entry, path) {
  if (path) {
    var rest = path[1];
    var id = path[0];
    return /* record */Block.record([
              "content",
              "id",
              "path",
              "children"
            ], [
              entry[/* content */0],
              entry[/* id */1],
              entry[/* path */2],
              List.map((function (child) {
                      if (child[/* id */1] === id) {
                        return deepUpdate(fn, child, rest);
                      } else {
                        return child;
                      }
                    }), entry[/* children */3])
            ]);
  } else {
    return Curry._1(fn, entry);
  }
}

function updateParent(fn, root, entry) {
  return deepUpdate(fn, root, ListRe.butLast(entry[/* path */2]));
}

function insertAfter(prev, item, root) {
  return deepUpdate((function (parent) {
                var match = Utils.splitOn((function (param) {
                        return eq(prev, param);
                      }), parent[/* children */3]);
                return /* record */Block.record([
                          "content",
                          "id",
                          "path",
                          "children"
                        ], [
                          parent[/* content */0],
                          parent[/* id */1],
                          parent[/* path */2],
                          List.concat(/* :: */Block.variant("::", [
                                  match[0],
                                  /* :: */Block.variant("::", [
                                      match[1],
                                      /* :: */Block.variant("::", [
                                          /* :: */Block.variant("::", [
                                              item,
                                              /* [] */0
                                            ]),
                                          /* :: */Block.variant("::", [
                                              match[2],
                                              /* [] */0
                                            ])
                                        ])
                                    ])
                                ]))
                        ]);
              }), root, ListRe.butLast(prev[/* path */2]));
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
exports.insertAfter = insertAfter;
/* shortid Not a pure module */
