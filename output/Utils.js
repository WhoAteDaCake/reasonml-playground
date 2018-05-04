'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Shortid = require("shortid");

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

var Dom = /* module */[
  /* targetValue */targetValue,
  /* eventToTarget */eventToTarget,
  /* eventToVal */eventToVal,
  /* eventToKeyCode */eventToKeyCode
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

exports.noProps = noProps;
exports.Dom = Dom;
exports.exclude = exclude;
exports.withoutLast = withoutLast;
/* noProps Not a pure module */
