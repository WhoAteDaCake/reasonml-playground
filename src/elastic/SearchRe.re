type t = {
  size: int,
  query: QueryRe.t,
  aggs: option(AggsRe.t),
  _source: option(list(string))
};