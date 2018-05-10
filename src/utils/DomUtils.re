let focus = (_id: string) => ();

module ReactEvent = {
  let keyboardTarget = event =>
    ReactEventRe.Form.target(event) |> Webapi.Dom.Element.unsafeAsHtmlElement;
};