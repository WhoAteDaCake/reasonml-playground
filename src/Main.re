[@bs.module "react-vega"] external reactVega : Js.t({..}) = "default";

let listenerName = str => reactVega##listenerName(str);

Js.log(listenerName("mad"));