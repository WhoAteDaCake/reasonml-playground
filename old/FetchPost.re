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
type reqBody = {size: int};

module Encode = {
  let reqBody = body => Json.Encode.(object_([("size", body.size |> int)]));
};

let searchkitUrl = "http://demo.searchkit.co/api/movies/_search";

let makeRequest = body =>
  Js.Promise.(
    Fetch.fetchWithInit(
      searchkitUrl,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Json.stringify(body)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        ()
      )
    )
    |> then_(Fetch.Response.text)
    |> then_(text => Json.parseOrRaise(text) |> Js.log |> resolve)
  );

makeRequest(Encode.reqBody({size: 1}));
/* module Decode = {
     let post = json =>
       Json.Decode.{
         userId: json |> field("userId", int),
         id: json |> field("id", int),
         title: json |> field("title", string),
         body: json |> field("body", string)
       };
     let parseOrRaise = Json.parseOrRaise;
   }; */
/* module Encode = {
     let post = data => Json.Encode.(object_([("size", data.id |> int)]));
   };

   let showId = post => Encode.post(post) |> Js.log;

   let test = Encode.post({userId: 1, id: 1, title: "test", body: "test"});

   Js.log(test); */
/* Js.Promise.(
     Fetch.fetch("https://jsonplaceholder.typicode.com/posts/1")
     |> then_(Fetch.Response.text)
     |> then_(text => Json.parseOrRaise(text) |> Decode.post |> showId |> resolve)
   ); */