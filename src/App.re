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
            className="row"
            onKeyDown=(event => {
              let code = Utils.Dom.eventToKeyCode(event);
              let content = event |> ReactEventRe.Keyboard.target |> Utils.Dom.targetValue;
              let newRoot = switch (code) {
              | 13 => {
                let path = Utils.withoutLast(item.path);
                Tree.addChild(state.root, path, "");
              }
              | 8 => {
                if (String.length(content) == 0) {
                  Tree.withoutChild(state.root, item)
                } else {
                  state.root
                }
              }
              | _ => state.root
            };
            send(Root(newRoot))
            })
            onChange=(event => {
              let content = Utils.Dom.eventToVal(event);
              let newRoot = Tree.walk(entry => {...entry, content }, state.root, item.path);
              send(Root(newRoot));
            })
          />,
        state.root.children
      );
    ReasonReact.createDomElement("div", ~props={ "className": "root"}, Array.of_list(items));
  }
};