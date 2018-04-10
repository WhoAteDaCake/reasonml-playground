module Query = ElasticKit.Query;

let search =
  ElasticKit.Client.search("http://demo.searchkit.co/api/movies/_search");

let myQuery: ElasticKit.Search.t = {size: 2, query: Bool(Must([Match_all]))};

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