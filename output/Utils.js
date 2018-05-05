'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Shortid = require("shortid");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");

var noProps = {
  key: Shortid.generate()
};

function targetValue(element) {
  return element.value;
}

function eventToTarget($$event) {
  return $$event.target;
}

function eventToVal($$event) {
  return $$event.target.value;
}

function eventToKeyCode($$event) {
  return $$event.which;
}

function getElementById(id) {
  return Js_primitive.null_undefined_to_opt(document.getElementById(id));
}

function focus(id) {
  var match = document.getElementById(id);
  if (match == null) {
    return /* () */0;
  } else {
    return match.focus();
  }
}

var Dom = /* module */[
  /* targetValue */targetValue,
  /* eventToTarget */eventToTarget,
  /* eventToVal */eventToVal,
  /* eventToKeyCode */eventToKeyCode,
  /* getElementById */getElementById,
  /* focus */focus
];

function exclude(predicate, list) {
  return List.fold_right((function (item, param) {
                var items = param[1];
                if (Curry._1(predicate, item)) {
                  return /* tuple */[
                          /* Some */[item],
                          items
                        ];
                } else {
                  return /* tuple */[
                          param[0],
                          /* :: */[
                            item,
                            items
                          ]
                        ];
                }
              }), list, /* tuple */[
              /* None */0,
              /* [] */0
            ]);
}

function withoutLast(ls) {
  return List.rev(List.tl(List.rev(ls)));
}

function last(ls) {
  return List.hd(List.rev(ls));
}

function find(predicate, list) {
  var result = List.filter(predicate)(list);
  if (List.length(result) === 0) {
    return /* None */0;
  } else {
    return /* Some */[List.nth(result, 0)];
  }
}

function splitOn(predicate, list) {
  return List.fold_left((function (param, item) {
                var right = param[2];
                var middle = param[1];
                var left = param[0];
                var match = Curry._1(predicate, item);
                var match$1 = +(List.length(middle) !== 0);
                var exit = 0;
                if (match !== 0) {
                  if (match$1 !== 0) {
                    exit = 1;
                  } else {
                    return /* tuple */[
                            left,
                            /* :: */[
                              item,
                              /* [] */0
                            ],
                            right
                          ];
                  }
                } else if (match$1 !== 0) {
                  exit = 1;
                } else {
                  return /* tuple */[
                          List.append(left, /* :: */[
                                item,
                                /* [] */0
                              ]),
                          middle,
                          right
                        ];
                }
                if (exit === 1) {
                  return /* tuple */[
                          left,
                          middle,
                          List.append(right, /* :: */[
                                item,
                                /* [] */0
                              ])
                        ];
                }
                
              }), /* tuple */[
              /* [] */0,
              /* [] */0,
              /* [] */0
            ], list);
}

exports.noProps = noProps;
exports.Dom = Dom;
exports.exclude = exclude;
exports.withoutLast = withoutLast;
exports.last = last;
exports.find = find;
exports.splitOn = splitOn;
/* noProps Not a pure module */
