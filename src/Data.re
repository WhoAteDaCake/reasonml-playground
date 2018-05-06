[@bs.val] external unsafeJsonParse : string => 'a = "JSON.parse";

let treeKey = "reason-react-todos";

let basePathKey = "reason-react-path";

let save = (which: string, item) =>
  switch (Js.Json.stringifyAny(item)) {
  | None => ()
  | Some(data) => Dom.Storage.(localStorage |> setItem(which, data))
  };

let load = (which: string) =>
  switch Dom.Storage.(localStorage |> getItem(which)) {
  | Some(data) => Some(unsafeJsonParse(data))
  | None => None
  };