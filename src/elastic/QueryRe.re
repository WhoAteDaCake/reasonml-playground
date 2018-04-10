type query =
  | Match_all
  | Match(string, string)
  | Bool(boolQuery)
and boolQuery =
  | Must(list(query))
  | Should(list(query))
  | Must_not(list(query));

type t = query;