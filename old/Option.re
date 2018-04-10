let map = (fn, opt) =>
  switch opt {
  | Some(value) => Some(fn(value))
  | None => None
  };