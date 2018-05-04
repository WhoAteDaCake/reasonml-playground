[@bs.module "shortid"] external sid : unit => string = "generate";

let noProps = {"key": sid()};

module Dom = {
  let targetValue = element : string => (element |> ReactDOMRe.domElementToObj)##value;
  let eventToTarget = event => event |> ReactEventRe.Form.target;
  let eventToVal = event => eventToTarget(event) |> targetValue;
  let eventToKeyCode = event => ReactEventRe.Keyboard.which(event);
};

let exclude = (predicate: 'a => bool, list: list('a)) : (option('a), list('a)) =>
  List.fold_right(
    (item, (found, items)) =>
      if (predicate(item)) {
        (Some(item), items);
      } else {
        (found, [item, ...items]);
      },
    list,
    (None, [])
  );