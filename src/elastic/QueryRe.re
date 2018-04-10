type query =
  | Match_all
  | Bool(boolQuery)
and boolQuery =
  | Must(list(query));

type t = query;