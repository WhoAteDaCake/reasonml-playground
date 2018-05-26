let focus = (_id: string) => ();

module ReactEvent = {
  let targetValue = element : string => (element |> ReactDOMRe.domElementToObj)##value;
  let keyboardValue = event =>
    ReactEventRe.Keyboard.target(event) |> targetValue;
};