[@bs.module "react-vega"] external reactVega : Js.t({..}) = "default";

[%raw "window.vega = ReactVega"];

let listenerName = str => reactVega##listenerName(str);