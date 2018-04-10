type search = SearchRe.t => Js.Json.t;

type query = QueryRe.t => Js.Json.t;

type boolQuery = QueryRe.boolQuery => Js.Json.t;

/* Temporary */
let matchAll = Json.Encode.(object_([("match_all", object_([]))]));

let rec query: query =
  spec =>
    switch spec {
    | Match_all => Json.Encode.(object_([("match_all", object_([]))]))
    | Bool(boolSpec) => Json.Encode.(object_([("bool", boolQuery(boolSpec))]))
    | _ => matchAll
    }
and boolQuery: boolQuery =
  spec =>
    switch spec {
    | Must(mustSpec) => Json.Encode.(object_([("must", query(mustSpec))]))
    | _ => matchAll
    };

let search: search =
  data =>
    Json.Encode.(
      object_([("size", data.size |> int), ("query", query(data.query))])
    );