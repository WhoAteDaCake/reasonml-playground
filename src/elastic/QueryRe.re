type query =
  | Match_all
  | Match(string, Type.value)
  | Bool(boolQuery)
and boolQuery =
  | Must(list(query))
  | Should(list(query))
  | Must_not(list(query));

type t = query;