type state = {
  root: Tree.entry,
  focus: string
};

type action =
  | Root(Tree.entry)
  | Focus(string)
  | FocusedRoot(Tree.entry, string);

let component = ReasonReact.reducerComponent("App");

let rootEntry = Tree.addChild(Tree.makeRoot(), [], "");

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
    let path = Utils.withoutLast(item.path);
    let child = Tree.makeEntry("", path);
    (Tree.walk(Tree.appendChild(child), root, path), child.id);
  | 8 =>
    /* Backspace */
    if (String.length(content) == 0) {
      (Tree.withoutChild(root, item), focus);
    } else {
      (root, focus);
    }
  | 18 =>
    /* Alt */
    let child = Tree.makeEntry("", item.path);
    (Tree.walk(Tree.appendChild(child), root, item.path), child.id);
  | 38 =>
    ReactEventRe.Keyboard.preventDefault(event);
    /* Arrow up */
    let above = Tree.walkUp(root, item, false);
    if (Tree.isSame(root, above)) {
      (root, focus);
    } else {
      (root, above.id);
    };
  | 40 =>
    ReactEventRe.Keyboard.preventDefault(event);
    /* Arrow up */
    let parentOpt: option(Tree.entry) =
      Tree.find(root, Utils.withoutLast(item.path));
    switch parentOpt {
    | None => (root, focus)
    | Some(parent) =>
      let (_, _, right) = Utils.splitOn(Tree.isSame(item), parent.children);
      if (List.length(right) != 0) {
        let prevChild: Tree.entry = List.hd(right);
        (root, prevChild.id);
      } else {
        (root, focus);
      };
    };
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
            event => {
              let content = Utils.Dom.eventToVal(event);
              send(
                Root(
                  Tree.walk(
                    entry => {...entry, content},
                    state.root,
                    item.path
                  )
                )
              );
            }
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