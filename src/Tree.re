type path = list(string);

type entry = {
  content: string,
  id: string,
  path,
  children: list(entry)
};

type entries = list(entry);

type update = entry => entry;

let rec walk = (updator: update, entry: entry, path: path) : entry =>
  switch path {
  | [] => updator(entry)
  | [id, ...rest] =>
    let updatedChildren =
      List.map(
        child =>
          if (child.id == id) {
            walk(updator, child, rest);
          } else {
            child;
          },
        entry.children
      );
    {...entry, children: updatedChildren};
  };

let rec find = (entry: entry, path: path): option(entry) => {
  switch path {
  | [] => Some(entry)
  | [id, ...rest] => {
    let childOpt = Utils.find(child => child.id == id, entry.children);
    switch (childOpt) {
    | Some(child) => find(child, rest)
    | None => None
    }
  }
  };
};

let makeEntry = (content: string, path: path) : entry => {
  let id = Utils.sid();
  {content, id, path: List.append(path, [id]), children: []};
};

let makeRoot = () => {content: "", id: Utils.sid(), path: [], children: []};

let appendChild = (child: entry, parent: entry) : entry => {
  ...parent,
  children: List.append(parent.children, [child])
};

let removeChild = (id: string, parent: entry): entry => {
  ...parent,
  children: List.filter(child => child.id != id, parent.children),
};

let addChild = (root: entry, path: path, content: string) : entry => {
  let child = makeEntry(content, path);
  walk(appendChild(child), root, path);
};

let withoutChild = (root: entry, child: entry): entry => {
  walk(removeChild(child.id), root, Utils.withoutLast(child.path))
};