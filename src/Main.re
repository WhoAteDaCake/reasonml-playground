module Query = ElasticKit.Query;

let search =
  ElasticKit.Client.search("http://demo.searchkit.co/api/movies/_search");

let myQuery: ElasticKit.Search.t = {
  size: 5,
  query: Bool(Must([Match("imdbRating", Float(8.9))])),
  _source: None,
  aggs:
    Some([
      ("writers", Terms("writers.raw", Int(10))),
      ("meta", Filter(Bool(Must([Term("type.raw", String("Movie"))]))))
    ])
};

/* User definitions */
type item = {title: string};

let itemParse = json => Json.Decode.{title: json |> field("title", string)};

/* User definitions */
Js.Promise.(
  search(myQuery |> ElasticKit.Encode.search)
  |> then_(resp =>
       ElasticKit.Decode.searchResult(itemParse, resp) |> Js.log |> resolve
     )
);

Js.log("sad");