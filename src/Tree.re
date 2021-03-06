type path = list(string);

type entry = {
  content: string,
  id: string,
  path,
  children
}
and children = list(entry);

type entries = list(entry);

type update = entry => entry;

let eq = (e1: entry, e2: entry) : bool => e1.id == e2.id;

let hasChildren = (entry: entry) : bool => List.length(entry.children) != 0;

let parentPath = (entry: entry) : list(string) => ListRe.butLast(entry.path);

let createEntry = (content: string, path: path) : entry => {
  let id = Utils.sid();
  {content, id, path: List.append(path, [id]), children: []};
};

let createRoot = (content: string) : entry => {
  content,
  id: Utils.sid(),
  path: [],
  children: []
};

let appendChild = (child: entry, parent: entry) : entry => {
  ...parent,
  children: List.append(parent.children, [child])
};

let removeChild = (id: string, parent: entry) : entry => {
  ...parent,
  children: List.filter(child => child.id != id, parent.children)
};

let updateContent = (content: string, entry: entry) : entry => {
  ...entry,
  content
};

let rec deepUpdate = (fn: update, entry: entry, path: path) : entry =>
  switch path {
  | [] => fn(entry)
  | [id, ...rest] => {
      ...entry,
      children:
        List.map(
          child =>
            if (child.id == id) {
              deepUpdate(fn, child, rest);
            } else {
              child;
            },
          entry.children
        )
    }
  };

let updateParent = (fn: update, root: entry, entry: entry) : entry =>
  deepUpdate(fn, root, parentPath(entry));

let insertAfter = (prev: entry, item: entry, root: entry) : entry =>
  deepUpdate(
    parent => {
      let (left, me, right) = Utils.splitOn(eq(prev), parent.children);
      {...parent, children: List.concat([left, me, [item], right])};
    },
    root,
    parentPath(prev)
  );
/*
 let rec find = (entry: entry, path: path) : option(entry) =>
   switch path {
   | [] => Some(entry)
   | [id, ...rest] =>
     let childOpt = Utils.find(child => child.id == id, entry.children);
     switch childOpt {
     | Some(child) => find(child, rest)
     | None => None
     };
   };


 let addChild = (root: entry, path: path, content: string) : entry => {
   let child = makeEntry(content, path);
   walk(appendChild(child), root, path);
 };

 let withoutChild = (root: entry, child: entry) : entry =>
   walk(removeChild(child.id), root, Utils.withoutLast(child.path));

 let rec lastChild = (item: entry) : entry =>
   if (List.length(item.children) == 0) {
     item;
   } else {
     lastChild(Utils.last(item.children));
   };

 let walkUp = (root: entry, item: entry) : entry =>
   switch (find(root, Utils.withoutLast(item.path))) {
   | Some(parent) =>
     let (left, _, _) = Utils.splitOn(isSame(item), parent.children);
     if (List.length(left) != 0) {
       lastChild(Utils.last(left));
     } else {
       parent;
     };
   | None => item
   };

 let rec walkUpWhile =
         (
           predicate: (entry, entry, list(entry)) => bool,
           root: entry,
           item: entry,
           visited: list(entry)
         )
         : (entry, list(entry)) => {
   let didVisit = [item, ...visited];
   switch (find(root, Utils.withoutLast(item.path))) {
   | None => (item, didVisit)
   | Some(parent) =>
     if (predicate(root, parent, didVisit)) {
       (parent, didVisit);
     } else {
       walkUpWhile(predicate, root, parent, didVisit);
     }
   };
 };

 let shouldStop = (root: entry, entry: entry, visited: list(entry)) : bool =>
   if (isSame(entry, root)) {
     true;
   } else {
     let (_, _, right) =
       Utils.splitOn(isSame(List.hd(visited)), entry.children);
     List.length(right) != 0;
   };

 let walkDown = (root: entry, item: entry) : entry =>
   if (hasChildren(item)) {
     List.hd(item.children);
   } else {
     switch (find(root, Utils.withoutLast(item.path))) {
     | Some(parent) =>
       let (_, _, right) = Utils.splitOn(isSame(item), parent.children);
       if (List.length(right) != 0) {
         List.hd(right);
       } else {
         let (found, visited) = walkUpWhile(shouldStop, root, item, []);
         if (isSame(found, root)) {
           item;
         } else {
           let (_, _, right) =
             Utils.splitOn(isSame(List.hd(visited)), found.children);
           List.hd(right);
         };
       };
     | None => item
     };
   };

 let insertAfter = (prev: entry, item: entry, root: entry) : entry =>
   walk(
     parent => {
       let (left, me, right) = Utils.splitOn(isSame(prev), parent.children);
       {...parent, children: List.concat([left, me, [item], right])};
     },
     root,
     parentPath(prev)
   ); */