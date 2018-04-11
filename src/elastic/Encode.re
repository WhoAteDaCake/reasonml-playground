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
      let rawValue =
        switch value {
        | String(v) => Json.Encode.string(v)
        | Float(v) => Json.Encode.float(v)
        | Int(v) => Json.Encode.int(v)
        };
      Json.Encode.(object_([("match", object_([(key, rawValue)]))]));
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

let source = spec => Json.Encode.(nullable(list(string), spec));

let search: search =
  data => {
    let list = [
      ("size", data.size |> Json.Encode.int),
      ("query", data.query |> query)
    ];
    let list =
      switch data._source {
      | Some(fields) =>
        List.append(list, [("_source", Json.Encode.(fields |> list(string)))])
      | None => list
      };
    Json.Encode.object_(list);
  };