type state = {root: Tree.entry};

type action =
  | Root(Tree.entry);

let initalId = Utils.sid();

let initialState = () => {
  root: Tree.addChild(Tree.makeRoot(), [], ""),
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer: (action: action, state) => switch (action) {
  | Root(root) => ReasonReact.Update({...state, root})
  },
  render: ({state, send}) => {
    let items =
      List.map(
      (item: Tree.entry) =>
          <input
            value=item.content
            onKeyDown=(event => {
              let code = Utils.Dom.eventToKeyCode(event);
              switch (code) {
              | 13 => {
                let path = List.rev(item.path) |> List.tl |> List.rev;
                let newRoot = Tree.addChild(state.root, path, "");
                send(Root(newRoot))
              }
              | _ => ()
            };
            })
            onChange=(event => {
              let content = Utils.Dom.eventToVal(event);
              let newRoot = Tree.walk(entry => {...entry, content }, state.root, item.path);
              send(Root(newRoot));
            })
          />,
        state.root.children
      );
    ReasonReact.createDomElement("div", ~props=Utils.noProps, Array.of_list(items));
  }
};