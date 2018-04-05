type stateMod('a) = 'a => 'a;

type t('a) = {
  .
  getState: unit => 'a,
  addModifier: stateMod('a) => t('a)
};

let addModifier = (modifier, state) => state#addModifier(modifier);

let getState = state => state#getState();

let rec createFull = (state: 'a, modifiers: list(stateMod('a))) : t('a) => {
  pub addModifier = modifier =>
    createFull(state, List.append(modifiers, [modifier]));
  pub getState = () => List.fold_left((a, f) => f(a), state, modifiers)
};

let create = (initialState: 'a) : t('a) => createFull(initialState, []);