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
/* type reqBody = {size: int};

   type item = {title: string};

   let itemParse = json => Json.Decode.{title: json |> field("title", string)};

   module Encode = {
     let reqBody = body => Json.Encode.(object_([("size", body.size |> int)]));
   };

   let client =
     ElasticKit.Client.search("http://demo.searchkit.co/api/movies/_search");

   let handleResp = resp => {
     let data: ElasticKit.searchResult(item) =
       ElasticKit.Decode.searchResult(itemParse, resp);
     let hits =
       switch data.hits {
       | Some(hits) => hits.hits
       | None => []
       };
     List.map(Js.log, hits);
     (); */
/* let resp = Option.map(hits => Js.log(take(hits)), data.hits);
   (); */
/* switch data.hits {
   | Some(d) => Js.log(d.hits)
   | None => ()
   }; */
/* Option.map(
     hits => {
       let actual: list(ElasticKit.hit(item)) = hits.hits;
       Js.log(actual);
     },
     data.hits
   ); */
/* Js.log(data.hits); */
/* List.map(Js.log, data.hits.hits); */
/* switch data.hits {
   | Some(hits) =>
     ();
   | None => Js.log("no hits")
   }; */
/* };

   Js.Promise.(
     client(Encode.reqBody({size: 2}))
     |> then_(resp => handleResp(resp) |> resolve)
   ); */
/* client(Encode.reqBody({size: 1})) */
/* |> Js.Promise.then_(resp => Js.Promise.resolve(Js.log(resp))); */
/*
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
   ); */
/* makeRequest(Encode.reqBody({size: 1})); */
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