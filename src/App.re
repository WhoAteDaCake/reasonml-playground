type state = {root: Tree.entry};

type action =
  | Root(Tree.entry);

let component = ReasonReact.reducerComponent("App");

let initialState = () => {root: Tree.addChild(Tree.makeRoot(), [], "")};

let make = _children => {
  ...component,
  initialState,
  reducer: (action: action, state) =>
    switch action {
    | Root(root) => ReasonReact.Update({...state, root})
    },
  render: ({state, send}) => {
    let rec renderItem = (item: Tree.entry) => {
      let items =
        switch item.children {
        | [] => <div className="hidden" />
        | _ =>
          ReasonReact.createDomElement(
            "div",
            ~props={"className": "children"},
            Array.of_list(List.map(renderItem, item.children))
          )
        };
      <div>
        <input
          value=item.content
          className="row"
          id=item.id
          onKeyDown=(
            event => {
              let code = Utils.Dom.eventToKeyCode(event);
              let content =
                event |> ReactEventRe.Keyboard.target |> Utils.Dom.targetValue;
              let newRoot =
                switch code {
                | 13 =>
                  /* Enter */
                  let path = Utils.withoutLast(item.path);
                  Tree.addChild(state.root, path, "");
                | 8 =>
                  /* Backspace */
                  if (String.length(content) == 0) {
                    Tree.withoutChild(state.root, item);
                  } else {
                    state.root;
                  }
                | 18 =>
                  /* Alt */
                  Tree.addChild(state.root, item.path, "")
                | _ => state.root
                };
              send(Root(newRoot));
            }
          )
          onChange=(
            event => {
              let content = Utils.Dom.eventToVal(event);
              let newRoot =
                Tree.walk(entry => {...entry, content}, state.root, item.path);
              send(Root(newRoot));
            }
          )
        />
        items
      </div>;
    };
    let items = List.map(renderItem, state.root.children);
    ReasonReact.createDomElement(
      "div",
      ~props={"className": "root"},
      Array.of_list(items)
    );
  }
};