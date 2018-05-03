[@bs.module "shortid"] external sid : unit => string = "generate";

let noProps = {"key": sid()};

module Dom = {
  let targetValue = element : string => (element |> ReactDOMRe.domElementToObj)##value;
  let toValueOnChange = event =>
    event |> ReactEventRe.Form.target |> targetValue;
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