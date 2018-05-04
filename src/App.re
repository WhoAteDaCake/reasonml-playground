type state = {root: Tree.entry};

type action =
  | Root(Tree.entry);

let component = ReasonReact.reducerComponent("App");

let initialState = () => {root: Tree.addChild(Tree.makeRoot(), [], "")};

let renderChildren = (item: Tree.entry, render) =>
  switch item.children {
  | [] => ReasonReact.null
  | _ =>
    <div className="children">
      <Fragment> (Array.of_list(List.map(render, item.children))) </Fragment>
    </div>
  };

let handleKey = (root: Tree.entry, item: Tree.entry, event) : Tree.entry => {
  let code = Utils.Dom.eventToKeyCode(event);
  let content = event |> ReactEventRe.Keyboard.target |> Utils.Dom.targetValue;
  switch code {
  | 13 =>
    /* Enter */
    let path = Utils.withoutLast(item.path);
    Tree.addChild(root, path, "");
  | 8 =>
    /* Backspace */
    if (String.length(content) == 0) {
      Tree.withoutChild(root, item);
    } else {
      root;
    }
  | 18 =>
    /* Alt */
    Tree.addChild(root, item.path, "")
  | _ => root
  };
};

let make = _children => {
  ...component,
  initialState,
  reducer: (action: action, state) =>
    switch action {
    | Root(root) => ReasonReact.Update({...state, root})
    },
  render: ({state, send}) => {
    let rec renderItem = (item: Tree.entry) =>
      <div key=item.id>
        <input
          value=item.content
          className="row"
          id=item.id
          onKeyDown=(event => send(Root(handleKey(state.root, item, event))))
          onChange=(
            event => {
              let content = Utils.Dom.eventToVal(event);
              let newRoot =
                Tree.walk(entry => {...entry, content}, state.root, item.path);
              send(Root(newRoot));
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