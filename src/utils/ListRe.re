let butLast = xs =>
  switch (Belt.List.take(xs, List.length(xs) - 1)) {
  | Some(x) => x
  | None => []
  };

let last = xs => Belt.List.getExn(xs, List.length(xs) - 1);

let seperate = (predicate, list) =>
  List.fold_left(
    ((left, middle, right), item) =>
      switch (predicate(item), List.length(middle) !== 0) {
      | (true, false) => (left, [item], right)
      | (false, false) => (List.append(left, [item]), middle, right)
      | _ => (left, middle, List.append(right, [item]))
      },
    ([], [], []),
    list
  );

let rec find = (predicate, ls) =>
  switch ls {
  | [] => None
  | [x, ...xs] =>
    if (predicate(x)) {
      Some(x);
    } else {
      find(predicate, xs);
    }
  };