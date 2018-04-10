type query =
  | Match_all
  | Bool(boolQuery)
and boolQuery =
  | Must(query);

type t = query;