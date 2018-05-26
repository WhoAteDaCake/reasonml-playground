let focus = (id: string) => {
  Js.log(id);
  let node = Webapi.Dom.Document.getElementById(id);
  Js.log(node);
};

module ReactEvent = {
  let targetValue = element : string => (element |> ReactDOMRe.domElementToObj)##value;
  let keyboardValue = event =>
    ReactEventRe.Keyboard.target(event) |> targetValue;
};