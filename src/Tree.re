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
    };
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

let walkUp = (root: entry, item: entry): entry =>
  switch (find(root, Utils.withoutLast(item.path))) {
  | Some(parent) =>
    let (left, me, _) = Utils.splitOn(isSame(item), parent.children);
    if (List.length(left) != 0) {
      lastChild(Utils.last(left))
    } else {
      parent
    }
  | None => item
  };

let rec walkUpWhile = (predicate: (entry, entry, list(entry)) => bool, root: entry, item: entry, visited: list(entry)):
  (entry, list(entry)) =>
 switch (find(root, Utils.withoutLast(item.path))) {
  | None => (item, visited)
  | Some(parent) =>
    if (predicate(root, parent, visited)) {
      (parent, visited);
    } else {
      walkUpWhile(predicate, root, parent, [parent, ...visited]);
    }
 };

let shouldStop = (root: entry, entry: entry, visited: list(entry)): bool => if (isSame(entry, root)) {
  true
} else {
  let (_, _, right) = Utils.splitOn(isSame(List.hd(visited)), entry.children);
  List.length(right) != 0;
};

let walkDown = (root: entry, item: entry): entry =>
  if (isSame(root, item)) {
    item;
  } else if (hasChildren(item)) {
    List.hd(item.children);
  } else {
    switch (find(root, Utils.withoutLast(item.path))) {
    | Some(parent) =>
      let (_, _, right) = Utils.splitOn(isSame(item), parent.children);
      if (List.length(right) != 0) {
        List.hd(right);
      } else {
        let (found, visited) = walkUpWhile(shouldStop, root, parent, [parent]);
        if (isSame(found, root)) {
          item;
        } else {
          let (_, _, right) = Utils.splitOn(isSame(List.hd(visited)), found.children);
          List.hd(right);
        }
        /* let (_, _, right) = Utils.splitOn(entry => List.exists(isSame(entry), visited), found.children);
        List.hd(right); */
      };
    | None => item
    };
  };