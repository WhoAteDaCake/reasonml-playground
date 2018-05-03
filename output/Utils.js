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

function toValueOnChange($$event) {
  return $$event.target.value;
}

var Dom = /* module */[
  /* targetValue */targetValue,
  /* toValueOnChange */toValueOnChange
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

exports.noProps = noProps;
exports.Dom = Dom;
exports.exclude = exclude;
/* noProps Not a pure module */
