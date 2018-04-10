type search = SearchRe.t => Js.Json.t;

type query = QueryRe.t => Js.Json.t;

type boolQuery = QueryRe.boolQuery => Js.Json.t;

/* Temporary */
let matchAll = Json.Encode.(object_([("match_all", object_([]))]));

let rec query: query =
  spec =>
    switch spec {
    | Match_all => Json.Encode.(object_([("match_all", object_([]))]))
    | Match(key, value) =>
      Json.Encode.(object_([("match", object_([(key, string(value))]))]))
    | Bool(boolSpec) => Json.Encode.(object_([("bool", boolQuery(boolSpec))]))
    | _ => matchAll
    }
and boolQuery: boolQuery =
  spec => {
    let (key, innerSpec) =
      switch spec {
      | Must(innerSpec) => ("must", innerSpec)
      | Should(innerSpec) => ("should", innerSpec)
      | Must_not(innerSpec) => ("should_not", innerSpec)
      };
    Json.Encode.(object_([(key, list(query, innerSpec))]));
  };

let search: search =
  data =>
    Json.Encode.(
      object_([("size", data.size |> int), ("query", query(data.query))])
    );