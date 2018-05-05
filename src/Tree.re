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

let isSame = (e1: entry, e2: entry) => e1.id == e2.id;

let hasChildren = (entry: entry): bool => List.length(entry.children) != 0;

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

let rec lastChild = (item: entry): entry => {
  if (List.length(item.children) == 0) {
    item
  } else {
    lastChild(Utils.last(item.children));
  }
};

/*
   First check if there is an entry above me
    If there is then go to last child of that entry
    If not, go to parent and repeat until root is reached,
      If we reach root, just return current focus
 */
let rec walkUp =
        (root: entry, item: entry, moved: bool): entry =>
  if (isSame(root, item)) {
    item;
  } else {
    let parentOpt: option(entry) =
      find(root, Utils.withoutLast(item.path));
    switch parentOpt {
    | Some(parent) =>
      let (left, me, _) = Utils.splitOn(isSame(item), parent.children);
      if (List.length(left) == 0) {
        if (moved) {
          List.nth(me, 0);
        } else {
          walkUp(root, parent, true);
        };
      } else {
        lastChild(Utils.last(left))
      };
    | None => item
    };
  };