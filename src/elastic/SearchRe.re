type t = {
  size: int,
  query: QueryRe.query,
  _source: option(list(string))
};