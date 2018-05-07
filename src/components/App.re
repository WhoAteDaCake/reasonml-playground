type state = {
  root: Tree.entry,
  focus: string,
  basePath: list(string)
};

type action =
  | Root(Tree.entry)
  | Focus(string)
  | FocusedRoot(Tree.entry, string)
  | UpdateBasePath(list(string));

/* To do:
     Extract functions using self.handle to pass send
     Move the circle icons to a seperate component to color on hover
     Standardise Tree types for id, path
   */
let component = ReasonReact.reducerComponent("App");

let rootEntry =
  switch (Data.load(Data.treeKey)) {
  | None => Tree.addChild(Tree.makeRoot("Home"), [], "")
  | Some(entry) => entry
  };

let renderChildren = (item: Tree.entry, render) =>
  switch item.children {
  | [] => ReasonReact.null
  | _ =>
    <div className="children">
      <Fragment> (Array.of_list(List.map(render, item.children))) </Fragment>
    </div>
  };

let handleKey =
    (root: Tree.entry, item: Tree.entry, event, focus: string)
    : (Tree.entry, string) => {
  let code = Utils.Dom.eventToKeyCode(event);
  let content = event |> ReactEventRe.Keyboard.target |> Utils.Dom.targetValue;
  switch code {
  | 13 =>
    /* Enter */
    let child = Tree.makeEntry("", Tree.parentPath(item));
    (Tree.insertAfter(item, child, root), child.id);
  | 8 =>
    /* Backspace */
    if (String.length(content) == 0) {
      let focused = Tree.walkUp(root, item);
      let root =
        Tree.walk(Tree.removeChild(item.id), root, Tree.parentPath(item));
      (root, focused.id);
    } else {
      (root, focus);
    }
  | 18 =>
    /* Alt */
    let child = Tree.makeEntry("", item.path);
    (Tree.walk(Tree.appendChild(child), root, item.path), child.id);
  | 38 =>
    /* Arrow up */
    (root, Tree.walkUp(root, item).id)
  | 40 =>
    /* Arrow down */
    (root, Tree.walkDown(root, item).id)
  | _ => (root, focus)
  };
};

let make = _children => {
  ...component,
  initialState: () => {
    root: rootEntry,
    focus: List.nth(rootEntry.children, 0).id,
    basePath: []
  },
  reducer: (action: action, state) =>
    switch action {
    | Root(root) => ReasonReact.Update({...state, root})
    | Focus(focus) => ReasonReact.Update({...state, focus})
    | FocusedRoot(root, focus) => ReasonReact.Update({...state, root, focus})
    | UpdateBasePath(basePath) => ReasonReact.Update({...state, basePath})
    },
  didUpdate: ({oldSelf, newSelf}) => {
    if (oldSelf.state.focus !== newSelf.state.focus) {
      Utils.Dom.focus(newSelf.state.focus);
    };
    Data.save(Data.treeKey, newSelf.state.root);
    ();
  },
  render: ({state, send}) => {
    /* Need root to just be one above */
    let root =
      switch (Tree.find(state.root, state.basePath)) {
      | Some(entry) => entry
      | None => state.root
      };
    let makeCrumb = (root, path) =>
      switch (Tree.find(root, path)) {
      | Some(item) =>
        <div onClick=(_e => send(UpdateBasePath(item.path))) key=(Utils.sid())>
          (ReasonReact.string(item.content))
        </div>
      | None => ReasonReact.null
      };
    let makeCrumbs = (entry: Tree.entry, path: list(string)) => {
      let (_, crumbs) =
        List.fold_left(
          ((count, items), _) => {
            let pathTo =
              switch (Belt.List.take(path, count)) {
              | Some(xs) => xs
              | None => []
              };
            Js.log(pathTo);
            (count + 1, Belt.List.add(items, makeCrumb(entry, pathTo)));
          },
          (1, []),
          path
        );
      crumbs;
    };
    let rec renderItem = (item: Tree.entry) =>
      <div key=item.id className="row">
        <div className="content">
          <div className="pad" onClick=(_e => send(UpdateBasePath(item.path)))>
            <i className="fas fa-circle" />
          </div>
          <input
            value=item.content
            id=item.id
            onKeyDown=(
              event => {
                let (newRoot, focus) =
                  handleKey(state.root, item, event, state.focus);
                send(FocusedRoot(newRoot, focus));
              }
            )
            onChange=(
              event =>
                send(
                  Root(
                    Tree.walk(
                      entry => {
                        ...entry,
                        content: Utils.Dom.eventToVal(event)
                      },
                      state.root,
                      item.path
                    )
                  )
                )
            )
          />
        </div>
        (renderChildren(item, renderItem))
      </div>;
    let crumbs =
      makeCrumbs(state.root, state.basePath)
      |> (ls => List.append([makeCrumb(state.root, [])], ls));
    <div className="root">
      <div className="header">
        <Fragment> (Array.of_list(crumbs)) </Fragment>
      </div>
      <div className="tree">
        <Fragment>
          (Array.of_list(List.map(renderItem, root.children)))
        </Fragment>
      </div>
    </div>;
  }
};