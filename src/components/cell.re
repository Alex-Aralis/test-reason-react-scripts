let component = ReasonReact.statelessComponent("Cell");



let style = ReactDOMRe.Style.make(
  ~width="50px", 
  ~height="50px", 
  ~borderWidth="2px",
  ()
);


let make = (~enabled, _children) => {
  ...component,
  render: (_self) => {
    let enabledStyle = ReactDOMRe.Style.make(
      ~backgroundColor=enabled ? "grey" : "white",
      ()
    );

    let style = ReactDOMRe.Style.combine(
      style,
      enabledStyle
    );

    <div style />;
  }
};
