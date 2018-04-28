type aggregation =
  | Terms(string, Type.value)
  | Term(string, Type.value)
  | Filter(aggregation)
  | Bool(boolAggregation)
and boolAggregation =
  | Must(list(aggregation))
  | Should(list(aggregation))
  | Must_not(list(aggregation));

type aggs = list((string, aggregation));

type t = aggs;