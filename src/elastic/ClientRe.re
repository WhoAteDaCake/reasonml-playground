let search = (url, body) =>
  Js.Promise.(
    Fetch.fetchWithInit(
      url,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Json.stringify(body)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        ()
      )
    )
    |> then_(Fetch.Response.text)
    |> then_(text => Json.parseOrRaise(text) |> resolve)
  );