type state = {
  root: Tree.entry,
  focus: option(Tree.entry),
  basePath: Tree.path
};

type action =
  | Root(Tree.entry)
  | FocusedRoot(Tree.entry, option(Tree.entry))
  | UpdateBasePath(list(string));

let rootEntry =
  switch (Data.load(Data.treeKey)) {
  | None =>
    Tree.createRoot("Home") |> Tree.appendChild(Tree.createEntry("", []))
  | Some(entry) => entry
  };

let renderChildren = (item: Tree.entry, render) =>
  switch item.children {
  | [] => ReasonReact.null
  | _ =>
    <div className="children">
      <Fragment> (Array.of_list(List.map(render, item.children))) </Fragment>
    </div>
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  let handleKey = (item: Tree.entry, event, self) => {
    /* let code = ReactEventRe.Keyboard.which(event);
       let content = DomUtils.ReactEvent.keyboardValue(event); */
    let (currentRoot, currentFocus) = (
      self.ReasonReact.state.root,
      self.ReasonReact.state.focus
    );
    let (root, focus) =
      switch (ReactEventRe.Keyboard.which(event)) {
      | 13 =>
        /* Enter */
        let child = Tree.createEntry("", Tree.parentPath(item));
        let root = Tree.insertAfter(item, child, currentRoot);
        (root, Some(child));
      | _ => (currentRoot, currentFocus)
      };
    Js.log(("pre-send", focus));
    self.ReasonReact.send(FocusedRoot(root, focus));
  };
  let handleChange = (item: Tree.entry, event, self) => {
    let content =
      ReactEventRe.Form.target(event) |> DomUtils.ReactEvent.targetValue;
    self.ReasonReact.send(
      Root(
        Tree.deepUpdate(
          Tree.updateContent(content),
          self.state.root,
          item.path
        )
      )
    );
  };
  {
    ...component,
    initialState: () => {root: rootEntry, focus: None, basePath: []},
    reducer: (action: action, state) => {
      switch action {
      | FocusedRoot(root, focus) => Js.log(("in-switch", focus))
      | _ => Js.log(("matched-all", action))
      };
      switch action {
      | Root(root) => ReasonReact.Update({...state, root})
      | FocusedRoot(root, focus) => ReasonReact.Update({...state, root, focus})
      | UpdateBasePath(basePath) => ReasonReact.Update({...state, basePath})
      };
    },
    didUpdate: ({oldSelf, newSelf}) =>
      if (! Belt.Option.eq(oldSelf.state.focus, newSelf.state.focus, Tree.eq)) {
        switch newSelf.state.focus {
        | Some(entry) => DomUtils.focus(entry.id)
        | None => ()
        };
      },
    render: self => {
      let rec renderItem = (item: Tree.entry) =>
        <div key=item.id className="row">
          <div className="content">
            <div className="pad"> <i className="fas fa-circle" /> </div>
            <input
              value=item.content
              id=item.id
              onKeyDown=(self.handle(handleKey(item)))
              onChange=(self.handle(handleChange(item)))
            />
          </div>
          (renderChildren(item, renderItem))
        </div>;
      <div className="root">
        <div className="header" />
        <div className="tree">
          <Fragment>
            (Array.of_list(List.map(renderItem, self.state.root.children)))
          </Fragment>
        </div>
      </div>;
    }
  };
};
/*

 let handleKey =
     (root: Tree.entry, item: Tree.entry, event, focus: string)
     : (Tree.entry, string) => {
   let code = Utils.Dom.eventToKeyCode(event);
   let content = event |> ReactEventRe.Keyboard.target |> Utils.Dom.targetValue;
   switch code {
   | 13 =>
     /* Enter */
     let child = Tree.makeEntry("", Tree.parentPath(item));
     (Tree.insertAfter(item, child, root), child.id);
   | 8 =>
     /* Backspace */
     if (String.length(content) == 0) {
       let focused = Tree.walkUp(root, item);
       let root =
         Tree.walk(Tree.removeChild(item.id), root, Tree.parentPath(item));
       (root, focused.id);
     } else {
       (root, focus);
     }
   | 18 =>
     /* Alt */
     let child = Tree.makeEntry("", item.path);
     (Tree.walk(Tree.appendChild(child), root, item.path), child.id);
   | 38 =>
     /* Arrow up */
     (root, Tree.walkUp(root, item).id)
   | 40 =>
     /* Arrow down */
     (root, Tree.walkDown(root, item).id)
   | _ => (root, focus)
   };
 };

 let make = _children => {
   ...component,
   initialState: () => {
     root: rootEntry,
     focus: List.nth(rootEntry.children, 0).id,
     basePath: []
   },
   reducer: (action: action, state) =>
     switch action {
     | Root(root) => ReasonReact.Update({...state, root})
     | Focus(focus) => ReasonReact.Update({...state, focus})
     | FocusedRoot(root, focus) => ReasonReact.Update({...state, root, focus})
     | UpdateBasePath(basePath) => ReasonReact.Update({...state, basePath})
     },
   didUpdate: ({oldSelf, newSelf}) => {
     if (oldSelf.state.focus !== newSelf.state.focus) {
       Utils.Dom.focus(newSelf.state.focus);
     };
     Data.save(Data.treeKey, newSelf.state.root);
     ();
   },
   render: ({state, send}) => {
     /* Need root to just be one above */
     let root =
       switch (Tree.find(state.root, state.basePath)) {
       | Some(entry) => entry
       | None => state.root
       };
     let makeCrumb = (root, path) =>
       switch (Tree.find(root, path)) {
       | Some(item) =>
         <div onClick=(_e => send(UpdateBasePath(item.path))) key=(Utils.sid())>
           (ReasonReact.string(item.content))
         </div>
       | None => ReasonReact.null
       };
     let makeCrumbs = (entry: Tree.entry, path: list(string)) => {
       let (_, crumbs) =
         List.fold_left(
           ((count, items), _) => {
             let pathTo =
               switch (Belt.List.take(path, count)) {
               | Some(xs) => xs
               | None => []
               };
             Js.log(pathTo);
             (count + 1, Belt.List.add(items, makeCrumb(entry, pathTo)));
           },
           (1, []),
           path
         );
       crumbs;
     };
     let rec renderItem = (item: Tree.entry) =>
       <div key=item.id className="row">
         <div className="content">
           <div className="pad" onClick=(_e => send(UpdateBasePath(item.path)))>
             <i className="fas fa-circle" />
           </div>
           <input
             value=item.content
             id=item.id
             onKeyDown=(
               event => {
                 let (newRoot, focus) =
                   handleKey(state.root, item, event, state.focus);
                 send(FocusedRoot(newRoot, focus));
               }
             )
             onChange=(
               event =>
                 send(
                   Root(
                     Tree.walk(
                       entry => {
                         ...entry,
                         content: Utils.Dom.eventToVal(event)
                       },
                       state.root,
                       item.path
                     )
                   )
                 )
             )
           />
         </div>
         (renderChildren(item, renderItem))
       </div>;
     let crumbs =
       makeCrumbs(state.root, state.basePath)
       |> (ls => List.append([makeCrumb(state.root, [])], ls));
     <div className="root">
       <div className="header">
         <Fragment> (Array.of_list(crumbs)) </Fragment>
       </div>
       <div className="tree">
         <Fragment>
           (Array.of_list(List.map(renderItem, root.children)))
         </Fragment>
       </div>
     </div>;
   }
 }; */