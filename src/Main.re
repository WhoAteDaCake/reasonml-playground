type initialState = list(string);

type state = State.t(initialState);

let append = (l1, l2) => List.append(l2, l1);

let state =
  State.create(["key0"])
  |> State.addModifier(append(["key1"]))
  |> State.addModifier(append(["key2"]));

Js.log(State.getState(state));