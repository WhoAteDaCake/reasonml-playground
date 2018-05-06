type state = {
  root: Tree.entry,
  focus: string
};

type action =
  | Root(Tree.entry)
  | Focus(string)
  | FocusedRoot(Tree.entry, string);

let component = ReasonReact.reducerComponent("App");

let rootEntry =
  switch (Data.load(Data.key)) {
  | None => Tree.addChild(Tree.makeRoot(), [], "")
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
    focus: List.nth(rootEntry.children, 0).id
  },
  reducer: (action: action, state) =>
    switch action {
    | Root(root) => ReasonReact.Update({...state, root})
    | Focus(focus) => ReasonReact.Update({...state, focus})
    | FocusedRoot(root, focus) => ReasonReact.Update({...state, root, focus})
    },
  didUpdate: ({oldSelf, newSelf}) => {
    if (oldSelf.state.focus !== newSelf.state.focus) {
      Utils.Dom.focus(newSelf.state.focus);
    };
    Data.save(Data.key, newSelf.state.root);
    ();
  },
  render: ({state, send}) => {
    let rec renderItem = (item: Tree.entry) =>
      <div key=item.id className="row">
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
                    entry => {...entry, content: Utils.Dom.eventToVal(event)},
                    state.root,
                    item.path
                  )
                )
              )
          )
        />
        (renderChildren(item, renderItem))
      </div>;
    <div className="root">
      <Fragment>
        (Array.of_list(List.map(renderItem, state.root.children)))
      </Fragment>
    </div>;
  }
};