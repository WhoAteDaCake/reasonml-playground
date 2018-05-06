'use strict';


function removeChild(_, parent) {
  return /* record */[
          /* content */parent[/* content */0],
          /* id */parent[/* id */1],
          /* path */parent[/* path */2],
          /* children : [] */0
        ];
}

exports.removeChild = removeChild;
/* No side effect */
