type shards = {
  total: int,
  successful: int,
  failed: int
};

type hit('item) = {
  _id: string,
  _index: string,
  _type: string,
  _score: float,
  _source: 'item
};

type hits('item) = {
  total: int,
  max_score: option(float),
  hits: list(hit('item))
};

type searchResult('item) = {
  took: option(int),
  timed_out: bool,
  shards,
  hits: option(hits('item)),
  error: option(string)
};

module Decode = {
  let hit = (item, json) =>
    Json.Decode.{
      _id: json |> field("_id", string),
      _index: json |> field("_index", string),
      _type: json |> field("_type", string),
      _score: json |> field("_score", float),
      _source: json |> field("_source", item)
    };
  let hits = (item, json) =>
    Json.Decode.{
      total: json |> field("total", int),
      max_score: json |> optional(field("max_score", float)),
      hits: json |> field("hits", list(hit(item)))
    };
  let shards = json =>
    Json.Decode.{
      total: json |> field("total", int),
      successful: json |> field("successful", int),
      failed: json |> field("failed", int)
    };
  let searchResult = (item, json) =>
    Json.Decode.{
      took: json |> optional(field("took", int)),
      timed_out: json |> field("timed_out", bool),
      shards: json |> field("_shards", shards),
      hits: json |> optional(field("hits", hits(item))),
      error: json |> optional(field("error", string))
    };
};

module Client = {
  let search = (url, body) =>
    Js.Promise.(
      Fetch.fetchWithInit(
        url,
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=Fetch.BodyInit.make(Json.stringify(body)),
          ~headers=
            Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          ()
        )
      )
      |> then_(Fetch.Response.text)
      |> then_(text => Json.parseOrRaise(text) |> resolve)
    );
};