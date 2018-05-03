type entry = {
  content: string,
  id: string,
  path: list(string),
  children: array(entry)
};

type state = {children: array(entry)};

type action =
  | Tick;

/* let textChange = ({ReasonReact.state, send}, event) => Js.log(event); */
let initalId = Utils.sid();

let initialState = () => {
  children: [|
    {content: "test", id: initalId, children: [||], path: [initalId]}
  |]
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer: (_action: action, _state) => ReasonReact.NoUpdate,
  render: ({state}) => {
    let items =
      Array.map(
        item =>
          <input
            value=item.content
            onChange=(event => Js.log(Utils.Dom.toValueOnChange(event)))
          />,
        state.children
      );
    ReasonReact.createDomElement("div", ~props=Utils.noProps, items);
  }
};