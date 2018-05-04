type path = list(string);

type entry = {
  content: string,
  id: string,
  path,
  children: list(entry)
};

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

let makeEntry = (content: string, path: path) : entry => {
  let id = Utils.sid();
  {content, id, path: List.append(path, [id]), children: []};
};

let makeRoot = () => {content: "", id: Utils.sid(), path: [], children: []};

let appendChild = (parent: entry, child: entry) : entry => {
  ...parent,
  children: List.append(parent.children, [child])
};

let removeChild = (id: string, parent: entry): entry => {
  ...parent,
  children: List.filter(child => child.id != id, parent.children),
};

let addChild = (root: entry, path: path, content: string) : entry => {
  let child = makeEntry(content, path);
  walk(entry => appendChild(entry, child), root, path);
};

let withoutChild = (root: entry, child: entry): entry => {
  walk(removeChild(child.id), root, Utils.withoutLast(child.path))
};