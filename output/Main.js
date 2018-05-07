'use strict';

var App = require("./components/App.js");
var ListRe = require("./utils/ListRe.js");
var ReactDOMRe = require("reason-react/lib/js/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

ReactDOMRe.renderToElementWithId(ReasonReact.element(/* None */0, /* None */0, App.make(/* array */[])), "app");

console.log(ListRe.find((function (x) {
            return +(x === 3);
          }), /* :: */[
          1,
          /* :: */[
            2,
            /* :: */[
              3,
              /* [] */0
            ]
          ]
        ]));

/*  Not a pure module */
