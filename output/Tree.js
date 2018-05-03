'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("./Utils.js");
var Shortid = require("shortid");

function makeChild(content, path) {
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

function noop(entry) {
  return /* record */[
          /* content */entry[/* content */0] + "hello",
          /* id */entry[/* id */1],
          /* path */entry[/* path */2],
          /* children */entry[/* children */3]
        ];
}

function walk(updator, entry, path) {
  if (path) {
    var id = path[0];
    var match = Utils.exclude((function (child) {
            return +(child[/* id */1] === id);
          }), entry[/* children */3]);
    var children = match[1];
    var excluded = match[0];
    var updatedChildren = excluded ? /* :: */[
        walk(updator, excluded[0], path[1]),
        children
      ] : children;
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

var child1 = makeChild("child1", /* [] */0);

var child2 = makeChild("child2", /* [] */0);

var initialEntry_001 = /* id */Shortid.generate();

var initialEntry_003 = /* children : :: */[
  child1,
  /* :: */[
    child2,
    /* [] */0
  ]
];

var initialEntry = /* record */[
  /* content */"test",
  initialEntry_001,
  /* path : [] */0,
  initialEntry_003
];

exports.makeChild = makeChild;
exports.noop = noop;
exports.walk = walk;
exports.child1 = child1;
exports.child2 = child2;
exports.initialEntry = initialEntry;
/* child1 Not a pure module */
