[@bs.module "shortid"] external sid : unit => string = "generate";
/*
 let noProps = {"key": sid()};

 /* Todo use Webapi for targets */
 module Dom = {
   let targetValue = element : string => (element |> ReactDOMRe.domElementToObj)##value;
   let eventToTarget = event => event |> ReactEventRe.Form.target;
   let eventToVal = event => eventToTarget(event) |> targetValue;
   let eventToKeyCode = event => ReactEventRe.Keyboard.which(event);
   let getElementById = id =>
     Webapi.Dom.Document.getElementById(id, Webapi.Dom.document);
   let focus = id =>
     switch (getElementById(id)) {
     | Some(element) => (element |> ReactDOMRe.domElementToObj)##focus()
     | None => ()
     };
 };

 let exclude = (predicate: 'a => bool, list: list('a)) : (option('a), list('a)) =>
   List.fold_right(
     (item, (found, items)) =>
       if (predicate(item)) {
         (Some(item), items);
       } else {
         (found, [item, ...items]);
       },
     list,
     (None, [])
   );

 let withoutLast = ls => List.rev(ls) |> List.tl |> List.rev;

 let last = ls => List.rev(ls) |> List.hd;

 let find = (predicate: 'a => bool, list: list('a)) : option('a) => {
   let result = List.filter(predicate, list);
   if (List.length(result) === 0) {
     None;
   } else {
     Some(List.nth(result, 0));
   };
 };

 let splitOn = (predicate, list) =>
   List.fold_left(
     ((left, middle, right), item) =>
       switch (predicate(item), List.length(middle) !== 0) {
       | (true, false) => (left, [item], right)
       | (false, false) => (List.append(left, [item]), middle, right)
       | _ => (left, middle, List.append(right, [item]))
       },
     ([], [], []),
     list
   ); */