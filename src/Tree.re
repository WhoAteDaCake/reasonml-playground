type path = list(string);

type entry = {
  content: string,
  id: string,
  path,
  children: list(entry)
};

type update = entry => entry;

let makeChild = (content: string, path: path) : entry => {
  let id = Utils.sid();
  {content, id, path: List.append(path, [id]), children: []};
};

let noop: update = entry => {...entry, content: entry.content ++ "hello"};

let rec walk = (updator: update, entry: entry, path: path) : entry =>
  switch path {
  | [] => updator(entry)
  | [id, ...rest] =>
    let (excluded, children) =
      Utils.exclude(child => child.id == id, entry.children);
    let updatedChildren =
      switch excluded {
      | Some(item) => [walk(updator, item, rest), ...children]
      | None => children
      };
    {...entry, children: updatedChildren};
  };

let child1 = makeChild("child1", []);

let child2 = makeChild("child2", []);

let initialEntry = {
  content: "test",
  id: Utils.sid(),
  path: [],
  children: [child1, child2]
};