/* http://demo.searchkit.co/api/movies/_search
   {
     "size": 20,
     "query": {
       "bool": {
         "should": [
           {
               "bool": {
                 "must": {
                   "match_phrase": {
                     "title": "The Dark Knight Rises"
                   }
                 }
               }
           }
         ]
       }
     },
   	"aggs": {
   		"filter123": {
   			"nested": {
   				"path": "released"
   			}
   		}
   	}
   } */
type post = {
  userId: int,
  id: int,
  title: string,
  body: string
};

type queryData = {size: int};

module Decode = {
  let post = json =>
    Json.Decode.{
      userId: json |> field("userId", int),
      id: json |> field("id", int),
      title: json |> field("title", string),
      body: json |> field("body", string)
    };
  let parseOrRaise = Json.parseOrRaise;
};

module Encode = {
  let post = data => Json.Encode.(object_([("size", data.id |> int)]));
};

let showId = post => Encode.post(post) |> Js.log;

let test = Encode.post({userId: 1, id: 1, title: "test", body: "test"});

Js.log(test);
/* Js.Promise.(
     Fetch.fetch("https://jsonplaceholder.typicode.com/posts/1")
     |> then_(Fetch.Response.text)
     |> then_(text => Json.parseOrRaise(text) |> Decode.post |> showId |> resolve)
   ); */