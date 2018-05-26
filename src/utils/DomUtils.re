/* let focus = (id: string) => {
     let node = Webapi.Dom.Document.getElementById(id);
     Js.log(node);
   }; */
let focus = _id => ();

module ReactEvent = {
  let targetValue = element : string => (element |> ReactDOMRe.domElementToObj)##value;
  let keyboardValue = event =>
    ReactEventRe.Keyboard.target(event) |> targetValue;
};