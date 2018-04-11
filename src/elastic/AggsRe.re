type value = Type.value;

type aggregation =
  | Terms(string, int);

type aggs = list((string, aggregation));

type t = aggs;