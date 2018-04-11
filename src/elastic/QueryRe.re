type value =
  | Float(float)
  | Int(int)
  | String(string);

type query =
  | Match_all
  | Match(string, value)
  | Bool(boolQuery)
and boolQuery =
  | Must(list(query))
  | Should(list(query))
  | Must_not(list(query));

type t = query;