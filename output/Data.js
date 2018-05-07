'use strict';


function save(which, item) {
  var match = JSON.stringify(item);
  if (match !== undefined) {
    localStorage.setItem(which, match);
    return /* () */0;
  } else {
    return /* () */0;
  }
}

function load(which) {
  var match = localStorage.getItem(which);
  if (match !== null) {
    return /* Some */[JSON.parse(match)];
  } else {
    return /* None */0;
  }
}

var treeKey = "tree-ls";

var basePathKey = "crumbs-ls";

exports.treeKey = treeKey;
exports.basePathKey = basePathKey;
exports.save = save;
exports.load = load;
/* No side effect */
