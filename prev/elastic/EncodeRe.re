type search = SearchRe.t => Js.Json.t;

type query = QueryRe.t => Js.Json.t;

type boolQuery = QueryRe.boolQuery => Js.Json.t;

type aggs = AggsRe.aggregation => Js.Json.t;

type aggsMap = AggsRe.t => list((string, Js.Json.t));

type boolAggregation = AggsRe.boolAggregation => Js.Json.t;

type takeRaw = Type.value => Js.Json.t;

let takeRaw: takeRaw =
  value =>
    switch value {
    | String(v) => Json.Encode.string(v)
    | Float(v) => Json.Encode.float(v)
    | Int(v) => Json.Encode.int(v)
    };

let rec query: query =
  spec =>
    switch spec {
    | Match_all => Json.Encode.(object_([("match_all", object_([]))]))
    | Match(key, value) =>
      Json.Encode.(object_([("match", object_([(key, takeRaw(value))]))]))
    | Bool(boolSpec) => Json.Encode.(object_([("bool", boolQuery(boolSpec))]))
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

/* Aggregations */
let rec aggs: aggs =
  spec =>
    switch spec {
    | Terms(key, value) =>
      Json.Encode.(
        object_([
          (
            "terms",
            object_([("field", string(key)), ("size", takeRaw(value))])
          )
        ])
      )
    | Term(key, value) =>
      Json.Encode.(object_([("term", object_([(key, takeRaw(value))]))]))
    | Filter(agg) => Json.Encode.(object_([("filter", aggs(agg))]))
    | Bool(boolAgg) =>
      Json.Encode.(object_([("bool", boolAggregation(boolAgg))]))
    }
and boolAggregation: boolAggregation =
  spec => {
    let (key, innerSpec) =
      switch spec {
      | Must(innerSpec) => ("must", innerSpec)
      | Should(innerSpec) => ("should", innerSpec)
      | Must_not(innerSpec) => ("should_not", innerSpec)
      };
    Json.Encode.(object_([(key, list(aggs, innerSpec))]));
  };

let aggsMap: aggsMap =
  list => List.map(((key, aggregation)) => (key, aggs(aggregation)), list);

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
    let list =
      switch data.aggs {
      | Some(aggregations) =>
        List.append(
          list,
          [("aggs", aggsMap(aggregations) |> Json.Encode.object_)]
        )
      | None => list
      };
    Json.Encode.object_(list);
  };